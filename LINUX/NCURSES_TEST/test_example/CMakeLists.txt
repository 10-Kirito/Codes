cmake_minimum_required(VERSION 3.15)
project(test_example)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ./test.cpp)

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})

