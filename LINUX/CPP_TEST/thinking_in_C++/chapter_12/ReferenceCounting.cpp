// Reference count, copy-on-write
#include "../required.h"
#include <iostream>
#include <ostream>
#include <string>
using namespace std;

class Dog {
  string _name;
  int _refcount;
  Dog(const string &name) : _name(name), _refcount(1) {
    cout << "Creating Dog: " << *this << endl;
  }

  // Prevent assignment:
  Dog &operator=(const Dog &rv);

public:
  // Dog can only be created on the heap:
  static Dog *make(const string &name) { return new Dog(name); }
  Dog(const Dog &d) : _name(d._name + "_copy"), _refcount(1) {
    cout << "Dog copy-constructor:" << *this << endl;
  }
  ~Dog() { cout << "Deleting Dog:" << *this << endl; }

  void attach() {
    ++_refcount;
    cout << "Attached Dog: " << *this << endl;
  }

  void detach() {
    require(_refcount != 0);
    cout << "Detaching Dog: " << *this << endl;

    if (--_refcount == 0)
      delete this;
  }

  // copy-on-write
  // Conditionally copy this Dog.
  // Call before modifying the Dog, assign resulting pointer to your Dog*.
  Dog *unalias() {
    cout << "Unaliasing Dog: " << *this << endl;
    // Don't duplicate if not aliased:
    if (_refcount == 1)
      return this;
    --_refcount;
    // use cppy-constructor to duplicate:
    return new Dog(*this);
  }

  void rename(const string &newName) {
    _name = newName;
    cout << "Dog renamed to: " << *this << endl;
  }

  friend ostream &operator<<(ostream &os, const Dog &d) {
    return os << "[" << d._name << "], refcount = " << d._refcount;
  }
};

class DogHouse {
  Dog *p;
  string houseName;

public:
  DogHouse(Dog *dog, const string &house) : p(dog), houseName(house) {
    cout << "Created DogHouse: " << *this << endl;
  }
  DogHouse(const DogHouse &dh)
      : p(dh.p), houseName("copy-constructor " + dh.houseName) {
    p->attach();
    cout << "DogHouse copy-constructor: " << *this << endl;
  }

  DogHouse &operator=(const DogHouse &dh) {
    // check for self-assignment
    if (&dh != this) {
      houseName = dh.houseName + " assigned";
      // clean up what you're using first;
      p->detach();
      p = dh.p;
      p->attach();
    }
    cout << "DogHouse operator= :" << *this << endl;
    return *this;
  }

  ~DogHouse() {
    cout << "DogHouse destructor:" << *this << endl;
    p->detach();
  }

  void renameHouse(const string& newName) {
    houseName = newName;
  }

  void unalias() {p = p->unalias();}

  // copy-on-write. Anytime you modify the contents of the pointer
  // you must first unalias it;
  void renameDog(const string& newName) {
    unalias();
    p->rename(newName);
  }

  // ...or when you allow someone else access:
  Dog* getDog() {
    unalias();
    return p;
  }

  friend ostream &operator<<(ostream &os, const DogHouse &dh) {
    return os << "[" << dh.houseName << "] contains " << *dh.p;
  }
};

int main (int argc, char *argv[])
{
  DogHouse fidos(Dog::make("Fido"), "FidoHouse"),
           spots(Dog::make("Spot"), "SpotHouse");
  cout << "Entering coyp-construction" << endl;
  DogHouse bobs(fidos);
  cout << "After copy-constructing bobs" << endl;
  cout << "fidos:" << fidos << endl;
  cout << "bobs:" << bobs << endl;
  cout << "Entering self-assignment" << endl;
  bobs = bobs;
  cout << "After self-assignment" << endl;
  cout << "bobs:" << bobs << endl;
  cout << "Entering rename(\"Bob\")" << endl;
  // Comment out the following lines:
  bobs.getDog()->rename("Bob");
  cout << "After rename(\"Bob\")" << endl;
  return 0;
}
