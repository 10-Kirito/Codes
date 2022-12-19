/*****************************************************************//**
 * \file   Test.cpp
 * \brief  
 * 
 * \author z1769
 * \date   December 2022
 *********************************************************************/

#include "A.h"

#include <iostream>

void dosomething(A a)
{
	std::cout << "Test the function of explicit! \n";
}

int main()
{
	A a;
	dosomething(a);
	/// 隐式转换发生在此处，如果我们传参传进来一个int类型的变量，函数会先判断可不可以对其隐式转换
	/// 为相应的变量类型，然后再去执行函数的功能；
	///	我们也可以去为我们自定义的类，说明它可不可以进行隐式类型转换，如果构造函数声明为explicit
	///	的话，就是告诉编译器，该处不可以进行隐式类型转换，但是并不影响其显式转换。
	dosomething(14);
	
	std::cout << "Hello World!\n";
}

