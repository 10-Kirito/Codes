cmake_minimum_required(VERSION 3.15)
project(ncurses_study)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})



add_subdirectory(hello_word)
add_subdirectory(first_example)
add_subdirectory(second_example)
add_subdirectory(test_example)
