#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <string>
#include "sequence_list.h"

TEST(sequence_list_test, init_list){
  seq_list sequence_list;
  sequence_list.init_list();
  // 测试顺序表的构造函数:
  EXPECT_EQ(sequence_list.empty(), true);
  EXPECT_EQ(sequence_list.size(), 20);
}

// 测试顺序表的插入
TEST(sequence_list_test, insert_list){
  seq_list sequence_list;
  sequence_list.init_list();

  for (int i = 0; i < 10; ++i) {
    sequence_list.insert_list(i + 1 , i + 1);
  }

  testing::internal::CaptureStdout();
  sequence_list.print_list();
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output, "{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}\n");
}

// 测试顺序表的删除
TEST(sequence_list_test, delete_list){
  seq_list sequence_list;
  sequence_list.init_list();

  for (int i = 0; i < 10; ++i) {
    sequence_list.insert_list(i + 1 , i + 1);
  }

  sequence_list.delete_list(1);
  testing::internal::CaptureStdout();
  sequence_list.print_list();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "{2, 3, 4, 5, 6, 7, 8, 9, 10}\n");

  sequence_list.delete_list(5);
  testing::internal::CaptureStdout();
  sequence_list.print_list();
  output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "{2, 3, 4, 5, 7, 8, 9, 10}\n");

  sequence_list.delete_list(8);
  testing::internal::CaptureStdout();
  sequence_list.print_list();
  output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "{2, 3, 4, 5, 7, 8, 9}\n");
}

// 测试顺序表的存取
TEST(sequence_list_test, getelem) {
  seq_list sequence_list;
  sequence_list.init_list();

  for (int i = 0; i < 10; ++i) {
    sequence_list.insert_list(i + 1 , i + 1);
  }

  int i = sequence_list.getElement(1);
  EXPECT_EQ(i, 1);
  EXPECT_EQ(sequence_list.length(), 10);

}


int main (int argc, char *argv[])
{
  // 初始化Goole Test
  ::testing::InitGoogleTest(&argc, argv);
  // 运行所有的测试用例
  return RUN_ALL_TESTS();
}

