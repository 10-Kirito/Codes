cmake_minimum_required(VERSION 3.15)
project(sequence_list_list)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(GTest REQUIRED)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${CMAKE_PROJECT_NAME} ./sequence_list_test.cpp ./sequence_list.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC GTest::GTest GTest::Main)
