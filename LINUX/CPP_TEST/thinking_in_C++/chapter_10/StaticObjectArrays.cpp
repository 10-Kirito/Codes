class X {
  int i;

public:
  X(int ii) : i(ii) {}
};

class Stat {
  static X x2;
  static X xTable2[];
  static const X x3;
  static const X xTablle3[];
};

X Stat::x2(100);

X Stat::xTable2[] = {X(1), X(2), X(3), X(4)};

const X Stat::x3(100);
const X Stat::xTablle3[] = {X(1), X(2), X(3), X(4)};

int main() { Stat v; }
