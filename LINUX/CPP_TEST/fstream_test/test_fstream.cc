#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

std::string Time() {
  std::time_t now = std::time(nullptr);
  std::tm *nowtm = std::localtime(&now);

  char file_name[1024];
  sprintf(file_name, "%d-%d-%d-log.txt", nowtm->tm_year + 1900,
          nowtm->tm_mon + 1, nowtm->tm_mday);
  return std::string(file_name);
}





int main() {

    std::string file_name = Time();
    std::ofstream file(file_name, std::ios::app);

    file << "error: \n test " << std::endl;
    file << "hello, world" << std::endl;
}