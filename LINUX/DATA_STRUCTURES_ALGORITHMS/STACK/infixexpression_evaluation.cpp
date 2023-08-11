#include "tools.h"
#include <iostream>
#include <stack>
#include <string>
/**
 *  简单的实现中缀表达式的计算（使用栈进行实现！）
 *
 */

/**
 * 中缀表达式的计算!
 * @param: infix_expression, 即将要计算的中缀表达式；
 * @param: result, 中缀表达式计算的结果，以引用的方式进行传递；
 * @return: return true if success, else false;
 */
bool infix_evaluation(std::string infix_expression, double &result) {

  // 使用栈实现中缀表达式的计算：
  //    我们需要使用两个栈来存储我们的数据：
  //      a. 操作数栈，用来存储我们的操作数；
  //      b. 运算符号栈，用来存储我们的运算符;
  //    1. 如果扫描到操作数的话，我们就将其直接压入操作数栈；
  //    2. 如果扫描到界限符号。如果遇到"(",直接将")"入栈即可；
  //    3.
  //    如果遇到")",依次弹出栈内的运算符号，并将操作数栈中的两个数字出栈，并进行计算，将结果入栈，直到遇到"("为止；
  //    4.
  //    如果遇到运算符号的话，依次弹出运算符栈中的优先级别高的或者等于当前运算符的所有符号，注意每一次出栈运算符号
  //       的时候，需要将操作数栈中的数字出栈，并进行计算，随之将结果入栈,当遇到"("或者栈为空的话停止计算；

  std::stack<double> _operand_stack;
  std::stack<char> _operator_stack;

  int i = 0;

  char c = infix_expression[i];

  int type;
  char c_temp;

  double operand_1, operand_2;
  while (c != '\0') {
    type = checkType(c);

    // 如果是操作数的话，1, 入栈：
    if (type == 1) {
      _operand_stack.push(c - '0');
    }

    // 如果是界限符号, 2：
    if (type == 2) {
      // 如果是‘(’，入栈
      if (c == '(') {
        _operator_stack.push(c);
      } else {
        // 如果是‘)’, 将操作符号里面的操作符号依次出栈，直到遇到'('，
        // '('也将其出栈
        c_temp = _operator_stack.top();
        while (c_temp != '(') {
          if (!_operand_stack.empty()) {
            operand_2 = _operand_stack.top();
            _operand_stack.pop();
          }
          if (!_operand_stack.empty()) {
            operand_1 = _operand_stack.top();
            _operand_stack.pop();
          }

          result = calculate(operand_1, operand_2, c_temp);
          _operand_stack.push(result);

          _operator_stack.pop();
          c_temp = _operator_stack.top();
        }

        // 将栈中的‘(’出栈。
        _operator_stack.pop();
      }
    }

    // 如果是运算符号, 3：
    if (type == 3) {
      if (!_operator_stack.empty()) {
        c_temp = _operator_stack.top();
        while (c_temp != '(' && !_operator_stack.empty() &&
               checkPriority(c, c_temp)) {
          if (!_operand_stack.empty()) {
            operand_2 = _operand_stack.top();
            _operand_stack.pop();
          }
          if (!_operand_stack.empty()) {
            operand_1 = _operand_stack.top();
            _operand_stack.pop();
          }

          result = calculate(operand_1, operand_2, c_temp);
          _operand_stack.push(result);

          _operator_stack.pop();
          if (!_operator_stack.empty()) {
            c_temp = _operator_stack.top();
          }
        }
      }
      _operator_stack.push(c);
    }

    ++i;
    c = infix_expression[i];
  }

  // 注意，当我们遍历完所有的字符串之后呢，此时操作数栈中应该还存在两个操作数，操作符栈中还存在一个操作符
  // 我们需要进行最后一次运算之后，猜得到真正的结果!!!
  c_temp = _operator_stack.top();
  if (!_operand_stack.empty()) {
    operand_2 = _operand_stack.top();
    _operand_stack.pop();
  }
  if (!_operand_stack.empty()) {
    operand_1 = _operand_stack.top();
    _operand_stack.pop();
  }

  result = calculate(operand_1, operand_2, c_temp);
  _operand_stack.push(result);

  return true;
}

int main(int argc, char *argv[]) {
  std::string temp = "((1+2)/2+3)*((2+3*(1+3))+2)";

  std::string infix_expression = "1+(2+3)-4";
  std::string postfix_expression;

  infix_to_postfix(temp, postfix_expression);

  std::cout << temp << std::endl;
  std::cout << postfix_expression << std::endl;
  double result;

  if (infix_evaluation(temp, result)) {
    std::cout << "计算成功:" << result << std::endl;
  } else {
    std::cout << "计算失败!" << std::endl;
  };

  return 0;
}
