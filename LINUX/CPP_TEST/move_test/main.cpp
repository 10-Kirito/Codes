#include <iostream>

class F {
  int a;

public:
  F(const int a_) : a(a_) {}
  friend void swap(F &, F &);
};

inline void swap(F &lhs, F &rhs) {
  using std::swap;
  std::cout << "inline void swap(F& lhs, F& rhs) is called!" << std::endl;
  std::swap(lhs.a, rhs.a);
}

class G {
public:
  F f;
  G(const F& f_) :f(f_){}
};

void swap(G& lhs, G& rhs) {
  using std::swap;
  swap(lhs.f, rhs.f);
}

int main(int argc, char *argv[]) {
  G a(F(1)), b(F(2));

  swap(a, b);

  return 0;
}
