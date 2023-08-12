#include <iostream>
using namespace std;

enum note { middleC, Csharp, Cflat };
class Instrument {
  int i;

public:
  virtual void play(note) const { cout << "Instrument::play" << endl; }
};

// Wind objects are Instruments
// because they have the same interface
class Wind : public Instrument {
  int j;
public:
  // override interface function:
  void play(note) const { cout << "Wind::play" << endl; }
};

void tune(Instrument &i) { i.play(middleC); }

int main(int argc, char *argv[]) {
  Wind flute;
  tune(flute);
  cout << "sizeof(Instrument) is " << sizeof(Instrument) << endl;
  cout << "sizeof(Wind) is " << sizeof(Wind) << endl;
  return 0;
}
