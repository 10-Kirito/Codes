cmake_minimum_required(VERSION 3.10)
project(spdlog_examples)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(spdlog REQUIRED)

add_executable(${PROJECT_NAME} ./hello.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog_header_only)
