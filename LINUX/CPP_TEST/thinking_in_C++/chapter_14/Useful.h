#ifndef USEFUL_H
#define USEFUL_H
#include <iostream>
class X {
  int x_i;

public:
  X() { x_i = 0; }
  void set(int ii) { x_i = ii; }
  int read() const { return x_i; }
  int permute() { return x_i = x_i * 47; }
  void print() { std::cout << "the value of x_i is " << x_i << std::endl; }
};
#endif // !USEFUL_H
