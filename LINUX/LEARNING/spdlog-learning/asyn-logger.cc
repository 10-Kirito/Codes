#include "spdlog/async.h" //support for async logging.
#include "spdlog/spdlog.h"
#include <iostream>
#include <spdlog/sinks/rotating_file_sink.h>
#include <thread>

int main(int, char *[]) {
  try {
    spdlog::init_thread_pool(24, 10);
    auto async_file = spdlog::rotating_logger_mt<spdlog::async_factory>(
        "test", "logs/test.log", 1024, 10);
    for (int i = 1; i < 1010; ++i) {
      async_file->info("Async message {}", std::hash<std::thread::id>{}(std::this_thread::get_id()));
    }
    // Under VisualStudio, this must be called before main finishes to
    // workaround a known VS issue
    spdlog::drop_all();
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log initialization failed: " << ex.what() << std::endl;
  }
}