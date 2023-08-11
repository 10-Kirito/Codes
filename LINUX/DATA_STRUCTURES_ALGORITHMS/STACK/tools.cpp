#include "tools.h"
#include <stdexcept>

bool isMatch(char temp, char top) {
  switch (temp) {
  case ')': {
    if (top != '(') {
      return false;
    }
    break;
  }
  case '}': {
    if (top != '{') {
      return false;
    }
    break;
  }
  case ']': {
    if (top != '[') {
      return false;
    }
    break;
  }
  }
  return true;
}

bool isMatchv1(char temp, char top) {
  if ((temp - top) == 1 || (temp - top) == 2) {
    return true;
  }
  return false;
}

bool checkExpression(std::string expression) {
  char c, temp;
  int i = 0;
  std::stack<char> _stack;

  while ((c = expression[i]) != '\0') {
    // 如果是三种括号的左边的符号，就入栈
    if (c == '(' || c == '[' || c == '{') {
      _stack.push(c);
    }

    // 如果是三种括号的右边的符号，就检查栈顶元素是否与其相等，如果相等就出栈；
    // 如果不相等，程序结束，返回false;
    if (c == ')' || c == ']' || c == '}') {
      temp = _stack.top();
      if (!isMatchv1(c, temp)) {
        return false;
      } else {
        if (!_stack.empty()) {
          _stack.pop();
        }
      }
    }
    ++i;
  }

  // 返回栈是否为空，如果为空的话，就会返回true，即括号匹配成功；
  // 如果不为空的话，就会返回false，即括号匹配失败;
  return _stack.empty();
}

int checkType(char c) {

  // 如果是数字的话，返回1；
  if (c >= 48 && c <= 57) {
    return 1;
  }
  // 如果c == (        )         [           ]          {            }
  if (c == 40 || c == 41 || c == 91 || c == 93 || c == 123 || c == 125) {
    return 2;
  }
  //        *          +          -          /
  if (c == 42 || c == 43 || c == 45 || c == 47) {
    return 3;
  }
  return -1;
}

bool checkPriority(char current, char top) {

  std::unordered_map<char, int> priority = {
      {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

  int priority_current = priority[current];
  int priority_top = priority[top];

  if (priority_current <= priority_top) {
    return true;
  }
  return false;
}

bool infix_to_postfix(std::string infix_expression,
                      std::string &postfix_expression) {

  // 进行检查，如果说中缀表达式中的括号存在不匹配情况，就会返回一个空的对象!
  if (!checkExpression(infix_expression)) {
    return false;
  }

  // 初始化一个栈，用来存储暂时还不能确定运算顺序的运算符
  // 从左到右依次处理各个元素，直至末尾。可能会遇到三种情况：
  //  1. 遇到操作数，直接加入后缀表达式；
  //  2.
  //  遇到界限符号。如果遇到"("，直接将"("入栈即可；如果遇到")"，依次弹出栈内的运算符号并且
  //  加入后缀表达式即可，直到遇到"("为止。（注意："(" 不加入后缀表达式中）；
  //  3.
  //  遇到运算符，依次弹出栈中优先级高于或者等于当前运算符的所有运算符号，并加入后缀表达式，
  //  如果碰到"("或者栈空的话就停止，如果没有的话，将当前运算符号入栈；
  //

  std::stack<char> _stack;
  int i = 0;
  // 如果中缀表达式为空的话，将后缀表达式置空即可
  if (infix_expression.empty()) {
    postfix_expression.clear();
    return true;
  }

  char c = infix_expression[i];

  int temp;
  char c_temp, c_temp_1;
  // 暂时先不考虑多位数字的情况，我们只考虑单位数字!
  while (c != '\0') {
    temp = checkType(c);
    // temp == 1,为数字；
    // temp == 2,为界限符号;
    // temp == 3,为运算符号；
    if (temp == 1) {
      postfix_expression += c;
    }

    if (temp == 2) {
      if (c == '(') {
        _stack.push(c);
      } else {
        // 如果是右括号的话，就将栈中的元素依次出栈，直到遇到'(',
        // 也将其出栈；
        c_temp = _stack.top();
        while (c_temp != '(') {
          postfix_expression += c_temp;
          _stack.pop();
          c_temp = _stack.top();
        }
        // 将'('出栈!
        _stack.pop();
      }
    }
    // 如果遇到运算符号的话，就依次弹出栈中优先级别高的字符，
    // 如果碰到'('或者栈空的话就停止弹出! 如果没有的话就将当前字符入栈!
    if (temp == 3) {
      if (!_stack.empty()) {
        c_temp = _stack.top();
        while (c_temp != '(' && !_stack.empty() && checkPriority(c, c_temp)) {
          postfix_expression += c_temp;
          _stack.pop();
          if (!_stack.empty()) {
            c_temp = _stack.top();
          }
        }
      }
      _stack.push(c);
    }
    ++i;
    c = infix_expression[i];
  }

  // 将栈中的内容弹出并追加到后缀表达式的后面:
  char final_temp;

  while (!_stack.empty()) {
    final_temp = _stack.top();
    postfix_expression += final_temp;
    _stack.pop();
  }
  return true;
}

double calculate(double operand_1, double operand_2, char operator_) {
  switch (operator_) {
  case '+':
    return operand_1 + operand_2;
  case '-':
    return operand_1 - operand_2;
  case '*':
    return operand_1 * operand_2;
  case '/': {
    if (operand_2 == 0) {
      throw std::logic_error("the second operand is 0");
    }
    return operand_1 / operand_2;
  }
  default:
    throw std::logic_error("operator error, '+' '-' '*' '/' ");
  }
}

/**
 * 后缀表达式的计算!
 * @param: postfix_expression, 即将要计算的后缀表达式；
 * @param: result, 后缀表达式计算的结果，以引用的方式进行传递；
 * @return: return true if success, else false;
 */
bool postfix_evaluation(std::string postfix_expression, double &result) {
  // 使用栈实现后缀表达式的计算(只需要一个栈用来存储数字即可)：
  //  1. 从左到右依次扫描下一个元素，直到处理完所有的元素；
  //  2. 如果扫描到操作数则入栈，并且读取下一个元素；
  //  3.
  //  如果扫描到运算符号的话，则出栈两个栈顶元素，并且执行相应的运算，并且将运算结果入栈，接着读取下一个元素；
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
      } else {
        // 如果此时栈为空的话，说明我们要计算的后缀表达式是有问题的!
        return false;
      }

      if (!_stack.empty()) {
        operand_2 = _stack.top();
        _stack.pop();
      } else {
        return false;
      }

      result = calculate(operand_2, operand_1, c);
      _stack.push(result);
    }

    ++i;
    c = postfix_expression[i];
  }
  result = _stack.top();
  return true;
  ;
}

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
