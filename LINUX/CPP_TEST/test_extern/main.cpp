#include "header.h"

#include <iostream>


extern const int test;

int main (int argc, char *argv[])
{
  std::cout << "来自别的文件的变量test, 其值为:" << test << std::endl;
  return 0;
}
