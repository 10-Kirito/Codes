/* 这里展示一些一元折叠的技巧*/

/* 技巧一：我们在打印一些参数的时候经常会遇到一些问题，比如说我们需要在前n-1个参数的
 * 后面输出一个间隔符号，比如说逗号一类的.*/
#include <iostream>
template<typename ...T>
void show_1(T... args){
  constexpr int last = sizeof ...(args) - 1;
  int i = 0;

  /*利用折叠展开式*/
  ((i < last ? (std::cout << args << "," ): (std::cout << args << std::endl), ++i), ...);
}

int main (int argc, char *argv[])
{
  show_1(1,2,3,4,5,6);
  
  return 0;
}
