/* 由于模板是在编译期间进行推导的，所以说其实不必通过函数的参数传递参数，允许直接将参数直接传递给模板*/

#include <iostream>
template <auto ...T>
void variadic_print() {
  ((std::cout << T), ...) << std::endl;
}

int main (int argc, char *argv[])
{
  variadic_print<1,2,3,4>();  
  return 0;
}
