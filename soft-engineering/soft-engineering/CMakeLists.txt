# =========================================================================
# 1. To generate Makefile under ./build: `cmake -B build`
# 2. To compile: `cmake --build build`
# =========================================================================

# Set the output directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

cmake_minimum_required(VERSION 3.22)
# The project name
project(soft_engineering)

# -std=c++11
set(CMAKE_CXX_STANDARD 11)

# Scan cpp files under directory 'source' recursively
file(GLOB SRC_DIR_LIST "source/*.cpp")
# Scan cpp files under directory 'test' recursively
file(GLOB TEST_DIR_LIST "test/*.cpp")

# Add third-party libs
add_subdirectory(./third-party-lib/googletest)

# Set libraries for master
set(LIBRARIES pthread)
# Set libraries for test branches
set(LIBRARIES_GTEST gtest pthread)

# Library target
add_library(soft_engineering_lib STATIC ${SRC_DIR_LIST})
target_link_libraries(soft_engineering_lib ${LIBRARIES})

add_library(soft_engineering_test_lib STATIC ${TEST_DIR_LIST})
target_link_libraries(soft_engineering_test_lib ${LIBRARIES_GTEST})

# Executable target
add_executable(soft_engineering ${SRC_DIR_LIST})
target_link_libraries(soft_engineering soft_engineering_lib)

# Test target
add_executable(soft_engineering_tests ${TEST_DIR_LIST})
target_link_libraries(soft_engineering_tests soft_engineering_test_lib gtest)
