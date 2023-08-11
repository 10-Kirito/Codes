#ifndef SEQUENCE_LIST_H
#define SEQUENCE_LIST_H

#define MAXSIZE 20

class seq_list{
private:
  int * _data;
  int _size;
  int _length;
  
public:
  seq_list() :_data(nullptr), _size(20), _length(0){}
  inline void init_list(){ _data = new int[MAXSIZE];}
  inline bool empty() { return _length == 0;}
  inline bool isfull() { return _size == _length;}
  inline int length() { return _length;}
  inline int size() { return _size;}
  bool insert_list(int location, int data);
  bool delete_list(int location);

  void print_list();

  int getElement(int location);
};
#endif // !SEQUENCE_LIST_H
