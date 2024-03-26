#include "spdlog/sinks/basic_file_sink.h"
#include <iostream>
#include <spdlog/common.h>
#include <spdlog/logger.h>

int main(int, char **) {
  try {
    // create basic file logger(not rotated)
    auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/basix.txt");

    my_logger->info("Welcome to spdlog!");
    my_logger->error("Some error message with arg: {}", 1);
    my_logger->warn("Easy padding in numbers like {:08d}", 12);
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log initialization failed" << ex.what() << std::endl;
  }
}