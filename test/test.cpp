
#include <iostream>
#include <cmath>
using namespace std;
 
template <class T>
class Compare
{
public:
     bool IsEqual(const T& arg, const T& arg1);
};
 
// 已经不具有template的意思了，已经明确为float了
template <>
class Compare<float>
{
public:
     bool IsEqual(const float& arg, const float& arg1);
};
 
// 已经不具有template的意思了，已经明确为double了
template <>
class Compare<double>
{
public:
     bool IsEqual(const double& arg, const double& arg1);
};
 
template <class T>
bool Compare<T>::IsEqual(const T& arg, const T& arg1)
{
     cout<<"Call Compare<T>::IsEqual"<<endl;
     return (arg == arg1);
}
 
bool Compare<float>::IsEqual(const float& arg, const float& arg1)
{
     cout<<"Call Compare<float>::IsEqual"<<endl;
     return (abs(arg - arg1) < 10e-3);
}
 
bool Compare<double>::IsEqual(const double& arg, const double& arg1)
{
     cout<<"Call Compare<double>::IsEqual"<<endl;
     return (abs(arg - arg1) < 10e-6);
}
 
int main()
{
     Compare<int> obj;
     Compare<float> obj1;
     Compare<double> obj2;
     cout<<obj.IsEqual(2, 2)<<endl;
     cout<<obj1.IsEqual(2.003, 2.002)<<endl;
     cout<<obj2.IsEqual(3.000002, 3.0000021)<<endl;
}
