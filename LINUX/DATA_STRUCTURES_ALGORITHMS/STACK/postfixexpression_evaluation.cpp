#include <cstdlib>
#include <iostream>
#include <ostream>
#include <stack>
#include <string>
#include "tools.h"

/**
 * 简单的实现了后缀表达式的计算!
 * (注意后缀表达式中只有数字和运算符号!!!)
 */


/**
 * 后缀表达式的计算!
 * @param: postfix_expression, 即将要计算的后缀表达式；
 * @param: result, 后缀表达式计算的结果，以引用的方式进行传递；
 * @return: return true if success, else false;
 */
bool postfix_evaluation(std::string postfix_expression, double & result) {
  // 使用栈实现后缀表达式的计算(只需要一个栈用来存储数字即可)：
  //  1. 从左到右依次扫描下一个元素，直到处理完所有的元素；
  //  2. 如果扫描到操作数则入栈，并且读取下一个元素；
  //  3. 如果扫描到运算符号的话，则出栈两个栈顶元素，并且执行相应的运算，并且将运算结果入栈，接着读取下一个元素；
  //
  int i = 0;
  char c = postfix_expression[i];
  std::stack<double> _stack;
  int type;
  double operand_1, operand_2;
  while (c != '\0') {
    type = checkType(c);
    // 如果是数字：
    if (type == 1) {
      _stack.push(c - '0');
    }
    // 如果是运算符号:
    if (type == 3) {
      if (!_stack.empty()) {
        operand_1 = _stack.top();
        _stack.pop();
      }else {
        // 如果此时栈为空的话，说明我们要计算的后缀表达式是有问题的!
        return false; 
      }

      if (!_stack.empty()) {
        operand_2 = _stack.top();
        _stack.pop();
      }else {
        return false;
      }

      result = calculate(operand_2, operand_1, c);
      _stack.push(result);
    }

    ++i;
    c = postfix_expression[i];
  }
  result = _stack.top();
  return true;;
}


int main (int argc, char *argv[])
{
  std::string infix_expression = "((1+2)/2+3)*((2+3*(1+3))+2)";
  std::string postfix_expression;

  if (infix_to_postfix(infix_expression, postfix_expression)) {
    std::cout << "中缀表达式为:" << infix_expression << std::endl;
    std::cout << "转化之后，后缀表达式为:" << postfix_expression << std::endl; 
  }else {
    std::cout << "中缀表达式转换失败!" << std::endl; 
  }

  double result;

 if( postfix_evaluation(postfix_expression, result)) {
   std::cout << "后缀表达式计算之后的结果为:" << result << std::endl;
 }else {
   std::cout << "后缀表达式计算失败!" << std::endl;
 }



  return 0;
}
