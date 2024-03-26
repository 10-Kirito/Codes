cmake_minimum_required(VERSION 3.10)
project(spdlog_example)

set(CMAKE_BUILD_TYPE Debug)
find_package(spdlog REQUIRED)

# add_executable(spdlog_example hello-world.cc)
# add_executable(spdlog_example basic-logger.cc)
# add_executable(spdlog_example rotating-logger.cc)
add_executable(spdlog_example asyn-logger.cc)

target_link_libraries(spdlog_example PRIVATE spdlog::spdlog)

