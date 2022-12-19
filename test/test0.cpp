
#include <iostream>
using namespace std;
 
// 一般化设计
template <class T, class T1>
class TestClass
{
public:
     TestClass()
     {
          cout<<"T, T1"<<endl;
     }
};
 
// 针对普通指针的偏特化设计
template <class T, class T1>
class TestClass<T*, T1*>
{
public:
     TestClass()
     {
          cout<<"T*, T1*"<<endl;
     }
};
 
// 针对const指针的偏特化设计
template <class T, class T1>
class TestClass<const T*, T1*>
{
public:
     TestClass()
     {
          cout<<"const T*, T1*"<<endl;
     }
};
 
int main()
{
     TestClass<int, char> obj;
     TestClass<int *, char *> obj1;
     TestClass<const int *, char *> obj2;
 
     return 0;
}
