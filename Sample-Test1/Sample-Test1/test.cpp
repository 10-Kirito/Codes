#include "pch.h"
#include <cstring>

using namespace std;
TEST(TestCaseName, TestName) {
  
	int* n = nullptr;
	ASSERT_NE(n, nullptr);
	ASSERT_EQ(1, 2);
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
	
	// 0. ������Ϣ��ӡ��
	// �����ǽ������Լ������ʧ����Ϣ��ֻ��Ҫʹ�������<< ���Զ�����Ϣ���䵽��Ӧ�ĺ꺯���м���
	// �����Ļ�������ǲ��Ե�ʱ������˴���ͻ��ӡ��Ӧ����Ϣ
	EXPECT_EQ(1, 1) << "1 and 2 is not equal";


}
	// 1. ʹ��TEST()����������������Ժ�������Щ�ǲ�����ֵ����ͨ��C++����
TEST(TestMyCode, TestFun) {
	// 2. ���Ժ����������������⣺
	
	// ������Ƕ�����һ�������TestMyCode, �����������һ�����Ե�Ԫ����TestFun
	// ��һ����������ΪTest Suite,�������׼���
	// �ڶ��������ǲ����׼��еĲ�������

	// ע�⣺�������ƶ���������Ч��C++��ʶ������Ӧ�ð����κ��»��ߡ�
	// ���Ե�ȫ�����ɰ�������Test Suits�Լ�����individual name����ɣ����Բ�ͬTest Suits�Ĳ��Կ��Ծ�����ͬ��individual name
	EXPECT_EQ(Factorial(1), 1);
	EXPECT_EQ(Factorial(2), 1) << "�����ķ���ֵΪ��" << Factorial(2);
	EXPECT_EQ(Factorial(3), 1) << "�����ķ���ֵΪ��" << Factorial(3);
}