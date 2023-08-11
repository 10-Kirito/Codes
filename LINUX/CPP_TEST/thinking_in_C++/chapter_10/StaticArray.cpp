class Values {
public:
  Values();
  Values(Values &&) = default;
  Values(const Values &) = default;
  Values &operator=(Values &&) = default;
  Values &operator=(const Values &) = default;
  ~Values();

private:
  static const int scSize = 100;
  static const long scLong = 100;

  static const int scInts[];
  static const long scLongs[];
  static const float scTable[];
  static const char scLetters[];
  static const float scFloat;
  static int size;
  static float table[];
  static char letters[];
};

int Values::size = 100;
float Values::table[] = {1.0, 1.2, 1.4};
char Values::letters[] = {'a', 'b', 'c', 'd'};

const float Values::scFloat = 1.1;
const int Values::scInts[] = {99, 100, 101, 102};
const long Values::scLongs[] = {99, 101, 12, 12};
const char Values::scLetters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

Values ::Values() {}

Values ::~Values() {}

int main(int argc, char *argv[]) {
  Values v;
  return 0;
}
