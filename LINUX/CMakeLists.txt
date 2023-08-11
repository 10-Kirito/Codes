cmake_minimum_required(VERSION 3.15)

project(test)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(GTest REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} ./main.cpp ./queue.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC GTest::GTest GTest::Main)
