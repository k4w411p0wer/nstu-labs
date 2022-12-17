#include "sorted_string_array.hpp"

#include <algorithm>
#include <compare>
#include <fstream>
#include <stdexcept>
#include <vector>

#ifndef NDEBUG
#include <cassert>
#include <iostream>
#endif

#define FILE_HEADER_SIZE                                                       \
  (sizeof(capacity_) + sizeof(size_) + sizeof(strings_) + sizeof(offset_))
#define MINIMAL_CAPACITY (1 << 4)
#define RESIZE_FACTOR (2)


void SortedStringArray::throw_if_not_open() {
  if (!is_open())
    throw FileNotOpen();
}

size_t SortedStringArray::_get_file_size() {
  seekg(0, std::fstream::beg);
  const auto beginp = tellg();
  seekg(0, std::fstream::end);
  const auto endp = tellg();
  return endp - beginp;
}

void SortedStringArray::_write(pos_type pos, const char *value, size_t size) {
  seekp(pos);
  write(value, size);
}

void SortedStringArray::_read(pos_type pos, char *buf, size_t size) {
  seekg(pos);
  read(buf, size);
}

void SortedStringArray::_read_header() {
  seekg(0);
  read(reinterpret_cast<char *>(&capacity_), sizeof(capacity_));
  read(reinterpret_cast<char *>(&size_), sizeof(size_));
  read(reinterpret_cast<char *>(&strings_), sizeof(strings_));
  read(reinterpret_cast<char *>(&offset_), sizeof(offset_));
}

void SortedStringArray::_write_header() {
  seekp(0);
  write(reinterpret_cast<const char *>(&capacity_), sizeof(capacity_));
  write(reinterpret_cast<const char *>(&size_), sizeof(size_));
  write(reinterpret_cast<const char *>(&strings_), sizeof(strings_));
  write(reinterpret_cast<const char *>(&offset_), sizeof(offset_));
}

void SortedStringArray::_alloc() {
  const auto offset = strings_ + capacity_ * sizeof(pos_type);
  seekp(offset_);
  for (; offset_ < offset; ++offset_)
    put(0);
}

void SortedStringArray::_resize() {
  pos_type old_strings = strings_;
  size_t old_size = size_;
  strings_ = offset_;
  capacity_ *= RESIZE_FACTOR;
  _alloc();

  for (size_t i = 0; i < old_size * sizeof(pos_type); ++i) {
    seekg(old_strings + i);
    char_type c = get();
    seekp(strings_ + i);
    put(c);
  }
}

double SortedStringArray::_get_used_memory_ratio() {
  size_t used_bytes = FILE_HEADER_SIZE + capacity_ * sizeof(pos_type);
  for (pos_type i = 0; i < size_; ++i)
    used_bytes += at(i).size() + sizeof(size_t);
  return static_cast<double>(used_bytes) / offset_;
}

SortedStringArray::SortedStringArray(const char *filename) {
  open(filename);
}

SortedStringArray::SortedStringArray(const std::string &filename)
    : SortedStringArray(filename.c_str()) {}

SortedStringArray::~SortedStringArray() {
  close();
}

void SortedStringArray::open(const char *filename) {
  bool is_empty = false;
  std::fstream::open(filename, in | out | binary);
  if (!is_open()) {
    is_empty = true;
    std::ofstream ofs(filename);
    ofs.close();
    std::fstream::open(filename, in | out | binary);
  }
  throw_if_not_open();

  capacity_ = MINIMAL_CAPACITY;
  size_ = 0;
  strings_ = FILE_HEADER_SIZE;
  offset_ = strings_ + capacity_ * sizeof(pos_type);


  if (is_empty || _get_file_size() < FILE_HEADER_SIZE) {
    _write_header();
    _alloc();
  } else {
    _read_header();
  }
  // seekg(0, end);
  // offset_ = tellg();
}

void SortedStringArray::open(const std::string &filename) {
  open(filename.c_str());
}

void SortedStringArray::close() {
  _write_header();
  std::fstream::close();
}

SortedStringArray::size_type SortedStringArray::size() const {
  return size_;
}

void SortedStringArray::add(const_reference str) {
  throw_if_not_open();
  seekp(offset_);
  const auto size = str.size();

  if (size_ + 1 > capacity_) {
    _resize();
  }

  pos_type pos = offset_;  // TODO optimizations
  _write(pos, reinterpret_cast<const char *>(&size), sizeof(size));
  _write(pos + sizeof(size), str.c_str(), sizeof(char) * size);
  _write(strings_ + (size_++) * sizeof(pos),
         reinterpret_cast<const char *>(&pos), sizeof(pos));
  offset_ = pos + sizeof(pos) + size;  // TODO change if optimize
}

SortedStringArray::value_type SortedStringArray::at(size_type index) {
  throw_if_not_open();
  if (index >= size_)
    throw std::out_of_range("array index out of range");

  pos_type pos = 0;
  _read(strings_ + index * sizeof(pos_type), reinterpret_cast<char *>(&pos),
        sizeof(pos));
  size_t size = 0;
  _read(pos, reinterpret_cast<char *>(&size), sizeof(size));

  seekg(pos + sizeof(size));
  std::string result(size, 0);
  for (pos_type i = 0; i < size; ++i)
    result[i] = get();
  return result;
}

void SortedStringArray::remove(size_type index) {
  throw_if_not_open();
  if (index >= size_)
    throw std::out_of_range("array index out of range");

  pos_type next_pos = 0;
  for (pos_type pos = index; pos + 1 < size_; ++pos) {
    _read((pos + 1) * sizeof(pos) + strings_,
          reinterpret_cast<char *>(&next_pos), sizeof(next_pos));
    _write(pos * sizeof(pos) + strings_, reinterpret_cast<char *>(&next_pos),
           sizeof(next_pos));
  }
  --size_;
}

void SortedStringArray::defragment() {
  throw_if_not_open();
  typedef struct {
    pos_type pos;
    pos_type index;
  } defrag_item;
  std::vector<defrag_item> strings(size_);

  for (pos_type i = 0; i < size_; ++i) {
    strings[i].index = i;
    _read(strings_ + i * sizeof(i), reinterpret_cast<char *>(&strings[i].pos),
          sizeof(strings[i].pos));
  }

  std::sort(strings.begin(), strings.end(),
            [](defrag_item &di1, defrag_item &di2) -> bool {
              return di1.pos < di2.pos;
            });

  bool shifted = false;
  pos_type new_offset = FILE_HEADER_SIZE;
  for (auto di : strings) {
    if (di.pos > strings_ && !shifted) {
      for (pos_type i = 0; i < capacity_; ++i) {
        pos_type p = 0;
        seekg(strings_ + i * sizeof(i));
        read(reinterpret_cast<char *>(&p), sizeof(i));
        seekp(new_offset + i * sizeof(i));
        write(reinterpret_cast<const char *>(&p), sizeof(i));
      }

      strings_ = new_offset;
      new_offset += capacity_ * sizeof(pos_type);
      shifted = true;
    }

    size_t size = 0;
    _read(di.pos, reinterpret_cast<char *>(&size), sizeof(size));
    _write(new_offset, reinterpret_cast<const char *>(&size), sizeof(size));

    di.pos += sizeof(size);
    new_offset += sizeof(size);
    for (size_t i = 0; i < size; ++i) {
      seekg(di.pos + i);
      char_type c = get();
      seekp(new_offset + i);
      put(c);
    }
    pos_type new_pos = new_offset - sizeof(size);
    _write(strings_ + di.index * sizeof(di.index),
           reinterpret_cast<const char *>(&new_pos), sizeof(new_pos));
    new_offset += size;
  }
  offset_ = new_offset;
  _write_header();
}

#ifndef NDEBUG
void SortedStringArray::print_debug_info() {
  std::cout << "[DEBUG INFO]" << std::endl;
  if (!is_open()) {
    std::cout << "File not open" << std::endl;
    return;
  }

  std::cout << "_get_file_size: " << _get_file_size() << '\n'
            << "capacity_: " << capacity_ << '\n'
            << "size_: " << size_ << '\n'
            << "strings_: " << strings_ << '\n'
            << "offset_: " << offset_ << '\n'
            << "used memory ratio: " << _get_used_memory_ratio() << std::endl;

  pos_type pos = 0;
  auto it = begin();
  for (pos_type i = 0; i < size_; ++i, ++it) {
    _read(strings_ + i * sizeof(pos_type), reinterpret_cast<char *>(&pos),
          sizeof(pos));
    auto str = *it;
    std::cout << "[" << i << "]: "
              << "(" << str.size() << ") "
              << "\"" << str << "\"" << std::endl;
  }
}
#endif

const char *SortedStringArray::FileNotOpen::what() const noexcept {
  return "File not open";
}

using ConstIterator = SortedStringArray::ConstIterator;

ConstIterator::ConstIterator(SortedStringArray *ssa)
    : ConstIterator::ConstIterator{ssa, 0} {}

ConstIterator::ConstIterator(SortedStringArray *ssa, size_type position)
    : ssa_{ssa}, position_{position} {}

ConstIterator::ConstIterator(const ConstIterator &other)
    : ssa_{other.ssa_}, position_{other.position_} {}

ConstIterator &ConstIterator::operator=(const ConstIterator &other) {
  if (this == &other)
    return *this;
  ssa_ = other.ssa_;
  position_ = other.position_;
  return *this;
}

// std::strong_ordering ConstIterator::operator<=>(const ConstIterator &other)
// const noexcept {
//   // if (auto cmp = ssa_ <=> other.ssa_; cmp != 0) return cmp;
//   return position_ <=> other.position_;
// };

ConstIterator &ConstIterator::operator++() {
  position_++;
  return *this;
}

ConstIterator ConstIterator::operator++(int) {
  ConstIterator res(*this);
  operator++();
  return res;
}

ConstIterator &ConstIterator::operator--() {
  position_--;
  return *this;
}

ConstIterator ConstIterator::operator--(int) {
  ConstIterator res(*this);
  operator--();
  return *this;
}

ConstIterator &ConstIterator::operator+=(size_type value) {
  position_ += value;
  return *this;
}

ConstIterator ConstIterator::operator+(size_type value) const {
  return ConstIterator{ssa_, position_ + value};
}

ConstIterator operator+(SortedStringArray::size_type value,
                        const ConstIterator &ci) {
  return ConstIterator{ci.ssa_, ci.position_ + value};
}

ConstIterator &ConstIterator::operator-=(size_type value) {
  position_ += value;
  return *this;
}

ConstIterator ConstIterator::operator-(size_type value) const {
  return ConstIterator{ssa_, position_ - value};
}

ConstIterator::difference_type
ConstIterator::operator-(ConstIterator ci) const {
  return position_ - ci.position_;
}

ConstIterator::value_type ConstIterator::operator*() const {
  return ssa_->at(position_);
}

ConstIterator::value_type ConstIterator::operator[](size_type offset) const {
  return ssa_->at(position_ + offset);
}

ConstIterator SortedStringArray::begin() const {
  return ConstIterator{const_cast<SortedStringArray *>(this), 0};
}

ConstIterator SortedStringArray::end() const {
  return ConstIterator{const_cast<SortedStringArray *>(this), size_};
}
