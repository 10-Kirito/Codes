#include <stack>
#include <iostream>

#define SCALE 8
/**
 * 本段代码是实现了栈的应用中的数制的转换的简单示例程序：
 */

int number_convert(int number) {
  std::stack<int> _stack;

  /**
   * 对要进行转换的数字不停的取余数，每次取完余数之后除以要转换到的进制，并将余数入栈：
   * 栈中从栈顶一次读取即为我们想要的数字！
   */
  while (number != 0) {
    _stack.push(number % SCALE);
    number = number / SCALE;
  }

  int result = 0;
  /**
   * 将栈中的数字合并起来，即每次先获取到对应的数字进行计算，随后将其出栈即可!
   */
  while (!_stack.empty()) {
    result  = result * 10 + _stack.top();
    _stack.pop();
  }
  return result;
}

int main (int argc, char *argv[])
{
  std::cout << "Please input the number you want to convert: ";
  int number;
  std::cin >> number;
  int result = number_convert(number);
  std::cout << "After convert the number is " << result << "("<< SCALE << ")"<< std::endl;
  return 0;
}
