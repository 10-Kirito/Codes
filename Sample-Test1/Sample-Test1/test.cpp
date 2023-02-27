#include "pch.h"
#include <cstring>

using namespace std;
TEST(TestCaseName, TestName) {
  
	int* n = nullptr;
	ASSERT_NE(n, nullptr);
	ASSERT_EQ(1, 2);
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
	
	// 0. 错误信息打印：
	// 这里是将我们自己定义的失败消息，只需要使用运算符<< 将自定义信息传输到相应的宏函数中即可
	// 这样的话如果我们测试的时候出现了错误就会打印相应的信息
	EXPECT_EQ(1, 1) << "1 and 2 is not equal";


}
	// 1. 使用TEST()宏来定义和命名测试函数，这些是不返回值的普通的C++函数
TEST(TestMyCode, TestFun) {
	// 2. 测试函数的两个参数问题：
	
	// 这里就是定义了一个组测试TestMyCode, 该组测试中有一个测试单元叫做TestFun
	// 第一个参数被称为Test Suite,即测试套件；
	// 第二个参数是测试套件中的测试名称

	// 注意：两个名称都必须是有效的C++标识符，不应该包含任何下划线。
	// 测试的全名是由包含它的Test Suits以及它的individual name所组成，来自不同Test Suits的测试可以具有相同的individual name
	EXPECT_EQ(Factorial(1), 1);
	EXPECT_EQ(Factorial(2), 1) << "函数的返回值为：" << Factorial(2);
	EXPECT_EQ(Factorial(3), 1) << "函数的返回值为：" << Factorial(3);
}