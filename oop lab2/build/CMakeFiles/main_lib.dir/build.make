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
CMAKE_SOURCE_DIR = "/root/mai-oop-labs/oop lab2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/root/mai-oop-labs/oop lab2/build"

# Include any dependencies generated for this target.
include CMakeFiles/main_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main_lib.dir/flags.make

CMakeFiles/main_lib.dir/src/five.cpp.o: CMakeFiles/main_lib.dir/flags.make
CMakeFiles/main_lib.dir/src/five.cpp.o: ../src/five.cpp
CMakeFiles/main_lib.dir/src/five.cpp.o: CMakeFiles/main_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/root/mai-oop-labs/oop lab2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main_lib.dir/src/five.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_lib.dir/src/five.cpp.o -MF CMakeFiles/main_lib.dir/src/five.cpp.o.d -o CMakeFiles/main_lib.dir/src/five.cpp.o -c "/root/mai-oop-labs/oop lab2/src/five.cpp"

CMakeFiles/main_lib.dir/src/five.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_lib.dir/src/five.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/root/mai-oop-labs/oop lab2/src/five.cpp" > CMakeFiles/main_lib.dir/src/five.cpp.i

CMakeFiles/main_lib.dir/src/five.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_lib.dir/src/five.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/root/mai-oop-labs/oop lab2/src/five.cpp" -o CMakeFiles/main_lib.dir/src/five.cpp.s

# Object files for target main_lib
main_lib_OBJECTS = \
"CMakeFiles/main_lib.dir/src/five.cpp.o"

# External object files for target main_lib
main_lib_EXTERNAL_OBJECTS =

libmain_lib.a: CMakeFiles/main_lib.dir/src/five.cpp.o
libmain_lib.a: CMakeFiles/main_lib.dir/build.make
libmain_lib.a: CMakeFiles/main_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/root/mai-oop-labs/oop lab2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmain_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/main_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main_lib.dir/build: libmain_lib.a
.PHONY : CMakeFiles/main_lib.dir/build

CMakeFiles/main_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main_lib.dir/clean

CMakeFiles/main_lib.dir/depend:
	cd "/root/mai-oop-labs/oop lab2/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/root/mai-oop-labs/oop lab2" "/root/mai-oop-labs/oop lab2" "/root/mai-oop-labs/oop lab2/build" "/root/mai-oop-labs/oop lab2/build" "/root/mai-oop-labs/oop lab2/build/CMakeFiles/main_lib.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/main_lib.dir/depend

