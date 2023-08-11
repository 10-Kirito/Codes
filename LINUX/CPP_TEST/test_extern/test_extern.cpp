// 测试extern "C"的一种用法
// 来自程序员的自我修养P90-91

#include <stdio.h>

namespace myname {
  int var = 42;
}

extern "C" int _ZN6myname3varE;

int main (int argc, char *argv[])
{
  printf("%d\n", _ZN6myname3varE);
  return 0;
}

