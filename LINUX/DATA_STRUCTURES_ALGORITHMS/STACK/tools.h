#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

/**
 *  辅助函数1:
 *  假设算法支持检查()、{}、[]三种括号
 *  下面就是简单的进行一个匹配检查!
 */
bool isMatch(char temp, char top);

/**
 *  辅助函数1_v1：
 * 检查三种括号是否匹配的话可以使用ASCII码进行检查，()后者减去前者为1；
 * {} 和 [] 后者减去前者为2， 所以说二者相减如果不是1或者2就说明匹配失败!
 */
bool isMatchv1(char temp, char top);

/**
 * 辅助函数2：
 * 检查表达式是否合法，仅仅简单的检查了括号匹配!
 */
bool checkExpression(std::string expression);

/**
 * 辅助函数3:
 * 该辅助函数负责检查单个字符的类型:
 *  1. 数字的话，返回1；
 *  2. 界限符号的话，返回2；
 *  3. 运算符号的话，返回3；
 *
 */
int checkType(char c);

/**
 * 辅助函数4：
 *  负责检查当前运算符是否比栈中的运算符优先级别高或者相等
 *  如果函数返回true, 则说明栈中的运算符优先级别更高；
 *  如果函数返回false, 则说明栈中的运算符号优先级别低;
 *
 *  (这里为了简单使用unorder_map来进行实现!)
 */
bool checkPriority(char current, char top);

/**
 * 中缀表达式转化为后缀表达式
 * @param infix_expression, 将要被转化的中缀表达式；
 * @param postfix_expression, 转化之后的结果；
 * @return true if success, else false;
 */
bool infix_to_postfix(std::string infix_expression,
                    std::string &postfix_expression);

/**
 * 两个数字的四则运算：
 * @param operand_1, 第一个操作数；
 * @param operand_2, 第二个操作数；
 * @param operator_, 操作符；
 * @return int, 返回计算结果；
 *
 * 如果存在逻辑错误的话，会抛出异常!
 *
 */
double calculate(double operand_1, double operand_2, char operator_);

/**
 * 后缀表达式的计算!
 * @param: postfix_expression, 即将要计算的后缀表达式；
 * @param: result, 后缀表达式计算的结果，以引用的方式进行传递；
 * @return: return true if success, else false;
 */
bool postfix_evaluation(std::string postfix_expression, double & result);


/**
 * 中缀表达式的计算!
 * @param: infix_expression, 即将要计算的中缀表达式；
 * @param: result, 中缀表达式计算的结果，以引用的方式进行传递；
 * @return: return true if success, else false;
 */
bool infix_evaluation(std::string infix_expression, double &result);

#endif // !TOOLS_H
