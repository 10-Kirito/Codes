#include<iostream>
#include<string>
#include<cstring>
#include<stack>
#include<cstdio>
#include<stdlib.h>
using namespace std;
#pragma warning(disable : 4996)
bool isOperator(string element) {
    if (element == "+" || element == "-" || element == "*" || element == "/") {
        return true;
    }
    return false;
}

int isRight(stack<string> prefix) {
    int temp = 0;
    int element = 0, symbol = 0;
begin:
    while (!prefix.empty()) {
        if (!isOperator(prefix.top())) {
            //cout << prefix.top() << "is element" << endl;
            if (temp) {
                //cout << "temp=" << temp << endl;
                break;
            }
            element++;
        }
        else {
            //cout << prefix.top() << "is symbol" << endl;
            symbol++;
            temp++;
        }
        prefix.pop();
    }
    if (element - symbol == 1) {
        if (!prefix.empty()) {
            element = 1;
            symbol = temp = 0;
            goto begin;
        }
        else return 1;
    }
    else return 0;
}




void PrefixToInfix(stack<string>& Stack_Prefix) {
    stack<string> Stack_Infix;
    string operand1, operand2, expression, str;
    double* result = new double[Stack_Prefix.size() + 1];
    float f;
    int i = 0;

    while (!Stack_Prefix.empty()) {
        // Get Infix expression from Prefix stack 
        str = Stack_Prefix.top();
        Stack_Prefix.pop();
        // check the string is or not digit
        if (!isOperator(str)) {
            Stack_Infix.push(str);
            sscanf(str.c_str(), "%f", &f);
            result[i++] = f;
        }
        else {//if the string is operator
            if (!Stack_Infix.empty()) {
                operand1 = Stack_Infix.top();
                Stack_Infix.pop();
            }else {
                cout << "Error" << endl;
                return;
            }
            if (!Stack_Infix.empty()) {
                operand2 = Stack_Infix.top();
                Stack_Infix.pop();
            }
            else {
                cout << "Error" << endl;
                return;
            }

            if (str == "*") {
                result[i - 2] = result[i - 1] * result[i - 2];
            }
            else if (str == "/")
            {
                if (result[i - 2] != 0) {
                    result[i - 2] = result[i - 1] / result[i - 2];
                }
                else {
                    cout << "Error" << endl;
                    return;
                }
            }
            else if (str == "+")
            {
                result[i - 2] = result[i - 1] + result[i - 2];
            }
            else if (str == "-")
            {
                result[i - 2] = result[i - 1] - result[i - 2];
            }
            i--;


            if (str == "*" || str == "/" || Stack_Prefix.empty()) {
                expression = operand1 + str + operand2;
                Stack_Infix.push(expression);
            }
            else {
                expression = "(" + operand1 + str + operand2 + ")";
                Stack_Infix.push(expression);
            }
        }
    }

    // Output the Infix expression and the result if there is no Error.
    // E.g. 
    // Input: * - 5 6 7
    // Output: (5-6)*7=-7
    cout << Stack_Infix.top() + "=" << result[0] << endl;
    //return Stack_Infix.top();
}
int main() {
    string prefix;
    stack<string> Stack_Prefix;

    int n_operator = 0;//number of opertors

    // Get the prefix elements by using cin and store the elements in Stack_Prefix
    while (cin >> prefix) {
        Stack_Prefix.push(prefix);
        // if input is char ,the count ++
        if (isOperator(prefix))
            n_operator++;
        if ('\n' == cin.get()) {
            break;
        }
    }

    // Get the size of stacks
    int infix_size = Stack_Prefix.size();
    int n_opearand = infix_size - n_operator;
    // You can use number of operators and the size of stacks to check if there is Error
    // The size of stacks must be 1 3 5 7 9 ??????
    // if ((infix_size - 1) % 2 != 0 || (infix_size == 1 && isOperator(Stack_Prefix.top()))) {
    if (n_opearand != (n_operator + 1) || (infix_size == 1 && isOperator(Stack_Prefix.top()))) {
        cout << "Error" << endl;
        return 0;
    }
    //if (!isRight(Stack_Prefix)) {
    //    cout << "Error2" << endl;
    //    return 0;
    //}


    // Call PrefixToInfix to output the Infix expression and the result if there is no Error.
    PrefixToInfix(Stack_Prefix);

    return 0;
}