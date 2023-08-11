#ifndef TEST_H
#define TEST_H

template <typename T> class Rect {
public:
  Rect(T l = 0.0f, T t = 0.0f, T r = 0.0f, T b = 0.0f)
      : left_(l), top_(t), right_(r), bottom_(b) {}

  void display();
  T left_;
  T top_;
  T right_;
  T bottom_;
};

#endif // !TEST_H
