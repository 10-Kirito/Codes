#ifndef GENERALIZED_LIST_H
#define GENERALIZED_LIST_H

#include <string>
typedef enum { ATOM, LIST } ElemTag;
template <typename Atom_type> struct Glist_node {
  ElemTag tag;
  union {
    Atom_type atom;
    struct Glist_node<Atom_type> *head_ptr;
  };
  struct Glist_node<Atom_type> *next_ptr;
};

template <typename Atom_type> class GList {
private:
  Glist_node<Atom_type> *glist;

public:
  GList() : glist(nullptr){};
  GList(std::string S);

  int glist_length();
  int glist_depth();
  bool glist_empty();
  Glist_node<Atom_type> get_head();
  GList<Atom_type> get_tail();
  void insert_first(int elem);
  Glist_node<Atom_type> delete_first();
  void tranverse_glist(void (*func)(Glist_node<Atom_type>));
};

#endif // !GENERALIZED_LIST_H
