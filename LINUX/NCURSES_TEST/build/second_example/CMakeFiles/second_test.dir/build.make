# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kirito/Desktop/ncurses_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kirito/Desktop/ncurses_test/build

# Include any dependencies generated for this target.
include second_example/CMakeFiles/second_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include second_example/CMakeFiles/second_test.dir/compiler_depend.make

# Include the progress variables for this target.
include second_example/CMakeFiles/second_test.dir/progress.make

# Include the compile flags for this target's objects.
include second_example/CMakeFiles/second_test.dir/flags.make

second_example/CMakeFiles/second_test.dir/main.cpp.o: second_example/CMakeFiles/second_test.dir/flags.make
second_example/CMakeFiles/second_test.dir/main.cpp.o: ../second_example/main.cpp
second_example/CMakeFiles/second_test.dir/main.cpp.o: second_example/CMakeFiles/second_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kirito/Desktop/ncurses_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object second_example/CMakeFiles/second_test.dir/main.cpp.o"
	cd /home/kirito/Desktop/ncurses_test/build/second_example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT second_example/CMakeFiles/second_test.dir/main.cpp.o -MF CMakeFiles/second_test.dir/main.cpp.o.d -o CMakeFiles/second_test.dir/main.cpp.o -c /home/kirito/Desktop/ncurses_test/second_example/main.cpp

second_example/CMakeFiles/second_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/second_test.dir/main.cpp.i"
	cd /home/kirito/Desktop/ncurses_test/build/second_example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kirito/Desktop/ncurses_test/second_example/main.cpp > CMakeFiles/second_test.dir/main.cpp.i

second_example/CMakeFiles/second_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/second_test.dir/main.cpp.s"
	cd /home/kirito/Desktop/ncurses_test/build/second_example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kirito/Desktop/ncurses_test/second_example/main.cpp -o CMakeFiles/second_test.dir/main.cpp.s

# Object files for target second_test
second_test_OBJECTS = \
"CMakeFiles/second_test.dir/main.cpp.o"

# External object files for target second_test
second_test_EXTERNAL_OBJECTS =

second_example/second_test: second_example/CMakeFiles/second_test.dir/main.cpp.o
second_example/second_test: second_example/CMakeFiles/second_test.dir/build.make
second_example/second_test: /usr/lib/x86_64-linux-gnu/libcurses.so
second_example/second_test: /usr/lib/x86_64-linux-gnu/libform.so
second_example/second_test: second_example/CMakeFiles/second_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kirito/Desktop/ncurses_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable second_test"
	cd /home/kirito/Desktop/ncurses_test/build/second_example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/second_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
second_example/CMakeFiles/second_test.dir/build: second_example/second_test
.PHONY : second_example/CMakeFiles/second_test.dir/build

second_example/CMakeFiles/second_test.dir/clean:
	cd /home/kirito/Desktop/ncurses_test/build/second_example && $(CMAKE_COMMAND) -P CMakeFiles/second_test.dir/cmake_clean.cmake
.PHONY : second_example/CMakeFiles/second_test.dir/clean

second_example/CMakeFiles/second_test.dir/depend:
	cd /home/kirito/Desktop/ncurses_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kirito/Desktop/ncurses_test /home/kirito/Desktop/ncurses_test/second_example /home/kirito/Desktop/ncurses_test/build /home/kirito/Desktop/ncurses_test/build/second_example /home/kirito/Desktop/ncurses_test/build/second_example/CMakeFiles/second_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : second_example/CMakeFiles/second_test.dir/depend
