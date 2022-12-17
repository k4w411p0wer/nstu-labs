#include <compare>
#include <cstddef>
#include <exception>
#include <fstream>
#include <ios>
#include <iterator>
#include <streambuf>
#include <string>


class SortedStringArray;


class SortedStringArray : public std::fstream {
  using pos_type = std::size_t;

  private:
  size_t capacity_;
  size_t size_;
  pos_type strings_;
  pos_type offset_;

  void throw_if_not_open();
  size_t _get_file_size();
  void _write(pos_type pos, const char *val, size_t size);
  void _read(pos_type pos, char *buf, size_t size);

  void _read_header();
  void _write_header();

  void _alloc();
  void _resize();

  public:
  using size_type = std::size_t;
  using value_type = std::string;
  using reference = std::string &;
  using const_reference = const std::string &;

  double _get_used_memory_ratio();
  SortedStringArray() = default;
  SortedStringArray(const char *filename);
  SortedStringArray(const std::string &filename);
  ~SortedStringArray();

  void open(const char *filename);
  void open(const std::string &filename);
  void close();
  size_type size() const;
  void add(const_reference str);
  value_type at(size_type index);
  void remove(size_type index);
  void defragment();
#ifndef NDEBUG
  void print_debug_info();
#endif
  class FileNotOpen : public std::exception {
    const char *what() const noexcept override;
  };
  struct ConstIterator;
  ConstIterator begin() const;
  ConstIterator end() const;
  // ConstIterator cbegin() const;
  // ConstIterator cend() const;
};

struct SortedStringArray::ConstIterator {
  using size_type = SortedStringArray::size_type;
  using iterator_category = std::random_access_iterator_tag;  // TODO: ?
  using difference_type = std::size_t;
  using value_type = std::string;
  using pointer = const std::string *;
  using reference = const std::string &;

  private:
  size_type position_;
  SortedStringArray *ssa_;

  public:
  ConstIterator(SortedStringArray *);
  ConstIterator(SortedStringArray *, size_type);
  ConstIterator(const ConstIterator &);
  ~ConstIterator() = default;

  ConstIterator &operator=(const ConstIterator &);
  std::strong_ordering
  operator<=>(const ConstIterator &) const noexcept = default;

  ConstIterator &operator++();
  ConstIterator operator++(int);
  ConstIterator &operator--();
  ConstIterator operator--(int);
  ConstIterator &operator+=(size_type);
  ConstIterator operator+(size_type) const;
  friend ConstIterator operator+(size_type, const ConstIterator &);
  ConstIterator &operator-=(size_type);
  ConstIterator operator-(size_type) const;
  difference_type operator-(ConstIterator) const;

  value_type operator*() const;
  value_type operator[](size_type) const;
};
