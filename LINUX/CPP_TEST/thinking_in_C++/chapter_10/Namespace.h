#ifndef NAMESPACE_H
#define NAMESPACE_H
#include <iostream>
namespace MyLib {
inline int func() {
  std::cout << "in namespace MyLib" << std::endl;
  return 1;
}
} // namespace MyLib
#endif // !NAMESPACE_H
