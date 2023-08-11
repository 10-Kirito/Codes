//
// pch.h
//

#pragma once

#include "gtest/gtest.h"

int Factorial(int n);


class QueueTest : public ::testing::Test {

};

//template <typename E>
//class Queue {
//public:
//	Queue();
//	void Enqueue(const E& element);
//	E* Dequeue();
//	size_t size() const;
//};
//
//template<typename E>
//inline Queue<E>::Queue()
//{
//}
//
//template<typename E>
//inline void Queue<E>::Enqueue(const E& element)
//{
//}
//
//template<typename E>
//inline E* Queue<E>::Dequeue()
//{
//	return nullptr;
//}
//
//template<typename E>
//inline size_t Queue<E>::size() const
//{
//	return size_t();
//}
