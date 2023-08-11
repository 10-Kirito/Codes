#include "test.h"
#include <iostream>

template <typename T> void Rect<T>::display() {
  std::cout << left_ << " " << top_ << " " << right_ << " " << bottom_
            << std::endl;
}
