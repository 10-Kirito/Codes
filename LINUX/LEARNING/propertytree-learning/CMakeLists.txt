cmake_minimum_required(VERSION 3.10)
project(loadconfig)
aux_source_directory(. SRC_FILES)

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.json DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)

find_package(Boost REQUIRED)
message(STATUS "${Boost_VERSION_MACRO}")

add_executable(loadconfig ${SRC_FILES})

target_include_directories(loadconfig PUBLIC "${Boost_INCLUDE_DIRS}")
target_link_libraries(loadconfig ${Boost_LIBRARIES})