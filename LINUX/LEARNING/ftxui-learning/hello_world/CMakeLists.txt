cmake_minimum_required(VERSION 3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main
)

FetchContent_MakeAvailable(ftxui
)
project(HelloWorld)
aux_source_directory(./src DIR_SRCS)
add_executable(HelloWorld ${DIR_SRCS})

target_link_libraries(HelloWorld PRIVATE ftxui::screen PRIVATE ftxui::dom PRIVATE ftxui::component)
