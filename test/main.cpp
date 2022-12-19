#include <iostream>
using namespace std;
 
template <class T>
class TClass
{
public:
     bool Equal(const T& arg, const T& arg1);
};
 
template <class T>
bool TClass<T>::Equal(const T& arg, const T& arg1)
{
     return (arg == arg1);
}
 
int main()
{
     TClass<double> obj;
     cout<<obj.Equal(2, 2)<<endl;
     cout<<obj.Equal(2.000003, 2.0000031)<<endl;
}
