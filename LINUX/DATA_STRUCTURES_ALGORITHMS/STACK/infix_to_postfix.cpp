#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

/**
 *  简单实现中缀表达式转化为后缀表达式，其中涉及到中缀表达式的合法性检查（本质上就是做一个括号匹配）
 */

/**
 *  辅助函数1:
 *  假设算法支持检查()、{}、[]三种括号
 *  下面就是简单的进行一个匹配检查!
 */
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

/**
 *  辅助函数1_v1：
 * 检查三种括号是否匹配的话可以使用ASCII码进行检查，()后者减去前者为1；
 * {} 和 [] 后者减去前者为2， 所以说二者相减如果不是1或者2就说明匹配失败!
 */
bool isMatchv1(char temp, char top) {
  if ((temp - top) == 1 || (temp - top) == 2) {
    return true;
  }
  return false;
}

/**
 * 辅助函数2：
 * 检查表达式是否合法，仅仅简单的检查了括号匹配!
 */
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

/**
 * 辅助函数3:
 * 该辅助函数负责检查单个字符的类型:
 *  1. 数字的话，返回1；
 *  2. 界限符号的话，返回2；
 *  3. 运算符号的话，返回3；
 *
 */
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

/**
 * 辅助函数4：
 *  负责检查当前运算符是否比栈中的运算符优先级别高或者相等
 *  如果函数返回true, 则说明栈中的运算符优先级别更高；
 *  如果函数返回false, 则说明栈中的运算符号优先级别低;
 *
 *  (这里为了简单使用unorder_map来进行实现!)
 */
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

/**
 * 中缀表达式转化为后缀表达式
 * @param infix_expression, 将要被转化的中缀表达式；
 * @param postfix_expression, 转化之后的结果；
 * @return true if success, else false;
 */
bool infix_to_postfix(std::string infix_expression,
                    std::string &postfix_expression) {

  // 进行检查，如果说中缀表达式中的括号存在不匹配情况，就会返回一个空的对象!
  if (!checkExpression(infix_expression)) {
    return false;
  }

  // 初始化一个栈，用来存储暂时还不能确定运算顺序的运算符
  // 从左到右依次处理各个元素，直至末尾。可能会遇到三种情况：
  //  1. 遇到操作数，直接加入后缀表达式；
  //  2. 遇到界限符号。如果遇到"("，直接将"("入栈即可；如果遇到")"，依次弹出栈内的运算符号并且
  //  加入后缀表达式即可，直到遇到"("为止。（注意："(" 不加入后缀表达式中）；
  //  3. 遇到运算符，依次弹出栈中优先级高于或者等于当前运算符的所有运算符号，并加入后缀表达式，
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

int main(int argc, char *argv[]) {

  std::string temp = "((1+2)/2+3)*((2+3*(1+3))+2)";

  std::string infix_expression = "1+(2+3)-4";
  std::string postfix_expression;

  infix_to_postfix(temp, postfix_expression);

  std::cout << temp << std::endl;
  std::cout << postfix_expression << std::endl;

  return 0;
}
