# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/build"

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/src/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/src/main.cpp.o -c "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/src/main.cpp"

CMakeFiles/main.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/src/main.cpp" > CMakeFiles/main.dir/src/main.cpp.i

CMakeFiles/main.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/src/main.cpp" -o CMakeFiles/main.dir/src/main.cpp.s

CMakeFiles/main.dir/src/manager.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/manager.cpp.o: ../src/manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/src/manager.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/src/manager.cpp.o -c "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/src/manager.cpp"

CMakeFiles/main.dir/src/manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/manager.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/src/manager.cpp" > CMakeFiles/main.dir/src/manager.cpp.i

CMakeFiles/main.dir/src/manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/manager.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/src/manager.cpp" -o CMakeFiles/main.dir/src/manager.cpp.s

CMakeFiles/main.dir/src/router.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/router.cpp.o: ../src/router.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/src/router.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/src/router.cpp.o -c "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/src/router.cpp"

CMakeFiles/main.dir/src/router.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/router.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/src/router.cpp" > CMakeFiles/main.dir/src/router.cpp.i

CMakeFiles/main.dir/src/router.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/router.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/src/router.cpp" -o CMakeFiles/main.dir/src/router.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/main.cpp.o" \
"CMakeFiles/main.dir/src/manager.cpp.o" \
"CMakeFiles/main.dir/src/router.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/src/main.cpp.o
main: CMakeFiles/main.dir/src/manager.cpp.o
main: CMakeFiles/main.dir/src/router.cpp.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology" "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology" "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/build" "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/build" "/Users/cwmchapman/Documents/Franklin and Marshall/Networks/cps373-assignments/04-topology/build/CMakeFiles/main.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

