// if we want to defined a exception by ourselves, we can inherit from
// base class exception like below:

#ifndef HEADER_H
#define HEADER_H

#include <exception>
class MyException : public std::exception {
  const char * what() const noexcept override{
    return "This exception is designed by myself!";
  }
};
#endif // !HEADER_H
