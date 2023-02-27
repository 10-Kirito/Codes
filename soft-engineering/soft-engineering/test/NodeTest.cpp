//
// Created by Liu Yuan on 2023/2/6.
//
#include "../source/Node.h"
#include <memory>
#include <gtest/gtest.h>

using node = NODE::Node<int>;

TEST(NodeTest, ConstructorTest) {
  node n1;
  EXPECT_EQ(0, n1.get_data());
  EXPECT_EQ(nullptr, n1.get_next().get());

  node n2(5);
  EXPECT_EQ(5, n2.get_data());
  EXPECT_EQ(nullptr, n2.get_next().get());

  node n3(10, &n1);
  EXPECT_EQ(10, n3.get_data());
  EXPECT_EQ(&n1, n3.get_next().get());
}