#include "file.hpp"

#include <ios>


File::File(const char *filename, std::ios_base::openmode mode) : _mode(mode) {
  _fs.open(filename, mode);
}

File::~File() {
  close();
}

void File::close() {
  _fs.close();
}

int File::getMode() {
  return static_cast<int>(_mode);
}


std::fstream &File::getFStream() {
  return _fs;
}
