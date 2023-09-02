#include <algorithm>
#include <cstdio>
#include <fstream>
#include <memory>
#include <string>

class FileDeleter {
private:
  std::string filename;

public:
  FileDeleter(const std::string &fn) : filename(fn) {}

  void operator()(std::ofstream *fp) {
    fp->close();
    // if the last pointer to the temporary file is deleted, we will delete the
    // file as well.
    std::remove(filename.c_str());
  }
};

int main(int argc, char *argv[]) {
  std::shared_ptr<std::ofstream> fp(new std::ofstream("temp.txt"),
                                    FileDeleter("temp.txt"));
  std::shared_ptr<std::ofstream> second(fp);
  return 0;
}
