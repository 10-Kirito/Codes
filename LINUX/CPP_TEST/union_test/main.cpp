#include <iostream>
#include <string>
#include <vector>
/**
 * Test union type:
 *
 * The test found that if the union contains those non-trivial
 * constructors, we need to define the corresponding constructors 
 * ourselves.
 *
 */

union Data {
  int int_value;
  float float_value;
  char a;
};

struct Node{
  union
  {
    int a;
    float b;
  };

};

int main(int argc, char *argv[]) {
  union Data data;
  data.int_value = 10;
  std::cout << sizeof(data);
  data.float_value = 10.0;
  std::cout << sizeof(data);
  data.a = 'c';
  std::cout << sizeof(data);
  std::cout << data.a << std::endl;
  
  Node node;
  node.a = 1;

  return 0;
}
