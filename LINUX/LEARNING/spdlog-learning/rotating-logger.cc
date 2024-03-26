#include "spdlog/sinks/rotating_file_sink.h"
#include <cstdio>
#include <ctime>
#include <iostream>
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <string>

std::string Time() {
  std::time_t now = std::time(nullptr);
  std::tm *nowtm = std::localtime(&now);

  char file_name[1024];
  sprintf(file_name, "%d-%d-%d-log.txt", nowtm->tm_year + 1900,
          nowtm->tm_mon + 1, nowtm->tm_mday);
  return std::string(file_name);
}

int main(int, char **) {
  try {

    std::string filename = "logs/" + Time();
    auto file_logger =
        spdlog::rotating_logger_mt("mylogger", filename, 1024, 10);
    for (int i = 0; i < 1000; ++i) {
      file_logger->info("Hello,world, {}", i);
    }
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log initialization failed: " << ex.what() << std::endl;
  }
}