cmake_minimum_required(VERSION 3.15)
project(first_test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
message(${CURSES_INCLUDE_DIR})

message(${CURSES_LIBRARIES})
add_executable(first_test ./main.cpp)

target_link_libraries(first_test ${CURSES_LIBRARIES})

