#include "Namespace.h"

namespace test = MyLib;
extern int func();
int main(int argc, char *argv[]) { 
  test::func();
  return 0; 
}
