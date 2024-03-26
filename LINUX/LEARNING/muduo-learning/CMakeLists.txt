cmake_minimum_required(VERSION 3.10)

project(ChatServer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ChatServer src/muduo_server.cpp)

target_link_libraries(ChatServer PUBLIC muduo_net muduo_base pthread)

