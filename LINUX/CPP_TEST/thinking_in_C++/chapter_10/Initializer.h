// Static initialization technique
//
#ifndef INITIALIZATIOIN_H
#define INITIALIZATIOIN_H
#include <iostream>
extern int x;
extern int y;

class Initializer {
  static int initCount;

public:
  Initializer() {
    std::cout << "Initializer()" << std::endl;
    // Initializer first time only
    if (initCount++ == 0) {
      std::cout << "Performing initialization" << std::endl;
      x = 100;
      y = 200;
    }
  }

  ~Initializer() {
    std::cout << "Performing cleanup" << std::endl;
  }
};

// THe following creates one object in each file where Initializer.h is included,
// but that object is only visible within that file;
static Initializer init;
#endif // !INITIALIZATIOIN_H
