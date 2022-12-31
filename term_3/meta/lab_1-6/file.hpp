#include <fstream>
#include <ios>


class File {
  private:
  int _mode;
  std::fstream _fs;

  public:
  File(const char *, std::ios_base::openmode);
  ~File();
  void close();
  int getMode();
  std::fstream &getFStream();
};
