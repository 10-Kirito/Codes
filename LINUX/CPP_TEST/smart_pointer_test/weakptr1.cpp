#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Person : public std :: enable_shared_from_this<Person> {
public:
  string name;
  shared_ptr<Person> mother;
  shared_ptr<Person> father;

  // vector<shared_ptr<Person>> kids;
  vector<weak_ptr<Person>> kids;

  Person(const string &n, shared_ptr<Person> m = nullptr,
         shared_ptr<Person> f = nullptr)
      : name(n), mother(m), father(f) {}

  ~Person() { cout << "delete " << name << endl; }

  void setParentAndTheirKids(shared_ptr<Person> m = nullptr,
                             shared_ptr<Person> f = nullptr) {

    mother = m;
    father = f;

    if (m) {
      m->kids.push_back(shared_ptr<Person>(shared_from_this()));
      // m->kids.push_back(shared_ptr<Person>(this));
    }
    if (f) {
      f->kids.push_back(shared_ptr<Person>(shared_from_this()));
      // f->kids.push_back(shared_ptr<Person>(this));
    }
  }
};

shared_ptr<Person> initFamily(const string &name) {
  shared_ptr<Person> mom = make_shared<Person>(name + "'s mom");
  shared_ptr<Person> father = make_shared<Person>(name + "'s father");

  shared_ptr<Person> kids = make_shared<Person>(name, mom, father);

  mom->kids.push_back(kids);
  father->kids.push_back(kids);

  return kids;
}

int main(int argc, char *argv[]) {
  shared_ptr<Person> p = initFamily("nico");

  cout << "nico's family exists" << endl;

  cout << "-nico is shared " << p.use_count() << " times" << endl;
  cout << "-name of 1st kid if nico's mom " << p->mother->kids[0].lock()->name
       << endl;

  p = initFamily("jim");
  cout << "jim's family exists" << endl;

  return 0;
}
