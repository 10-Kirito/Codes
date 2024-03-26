#include <iostream>
#include <unistd.h>

int main(int argc, char **argv) {
  std::cout << (char)getopt(argc, argv, "i:") << std::endl;
  std::cout << optarg << std::endl;
  std::cout << optind << std::endl;
  std::cout << opterr << std::endl;
  std::cout << optopt << std::endl;

  return 0;
}