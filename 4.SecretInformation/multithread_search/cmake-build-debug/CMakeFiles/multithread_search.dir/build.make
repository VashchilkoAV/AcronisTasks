# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/alexander/computer_science/IDEs/apps/CLion/ch-0/201.7223.86/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/alexander/computer_science/IDEs/apps/CLion/ch-0/201.7223.86/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alexander/computer_science/projects/multithread_search/multithread_search

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexander/computer_science/projects/multithread_search/multithread_search/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/multithread_search.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/multithread_search.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/multithread_search.dir/flags.make

CMakeFiles/multithread_search.dir/main.cpp.o: CMakeFiles/multithread_search.dir/flags.make
CMakeFiles/multithread_search.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexander/computer_science/projects/multithread_search/multithread_search/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/multithread_search.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multithread_search.dir/main.cpp.o -c /home/alexander/computer_science/projects/multithread_search/multithread_search/main.cpp

CMakeFiles/multithread_search.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multithread_search.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexander/computer_science/projects/multithread_search/multithread_search/main.cpp > CMakeFiles/multithread_search.dir/main.cpp.i

CMakeFiles/multithread_search.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multithread_search.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexander/computer_science/projects/multithread_search/multithread_search/main.cpp -o CMakeFiles/multithread_search.dir/main.cpp.s

CMakeFiles/multithread_search.dir/KMP.cpp.o: CMakeFiles/multithread_search.dir/flags.make
CMakeFiles/multithread_search.dir/KMP.cpp.o: ../KMP.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexander/computer_science/projects/multithread_search/multithread_search/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/multithread_search.dir/KMP.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multithread_search.dir/KMP.cpp.o -c /home/alexander/computer_science/projects/multithread_search/multithread_search/KMP.cpp

CMakeFiles/multithread_search.dir/KMP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multithread_search.dir/KMP.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexander/computer_science/projects/multithread_search/multithread_search/KMP.cpp > CMakeFiles/multithread_search.dir/KMP.cpp.i

CMakeFiles/multithread_search.dir/KMP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multithread_search.dir/KMP.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexander/computer_science/projects/multithread_search/multithread_search/KMP.cpp -o CMakeFiles/multithread_search.dir/KMP.cpp.s

CMakeFiles/multithread_search.dir/file_manager.cpp.o: CMakeFiles/multithread_search.dir/flags.make
CMakeFiles/multithread_search.dir/file_manager.cpp.o: ../file_manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexander/computer_science/projects/multithread_search/multithread_search/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/multithread_search.dir/file_manager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multithread_search.dir/file_manager.cpp.o -c /home/alexander/computer_science/projects/multithread_search/multithread_search/file_manager.cpp

CMakeFiles/multithread_search.dir/file_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multithread_search.dir/file_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexander/computer_science/projects/multithread_search/multithread_search/file_manager.cpp > CMakeFiles/multithread_search.dir/file_manager.cpp.i

CMakeFiles/multithread_search.dir/file_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multithread_search.dir/file_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexander/computer_science/projects/multithread_search/multithread_search/file_manager.cpp -o CMakeFiles/multithread_search.dir/file_manager.cpp.s

CMakeFiles/multithread_search.dir/threads_manager.cpp.o: CMakeFiles/multithread_search.dir/flags.make
CMakeFiles/multithread_search.dir/threads_manager.cpp.o: ../threads_manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexander/computer_science/projects/multithread_search/multithread_search/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/multithread_search.dir/threads_manager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multithread_search.dir/threads_manager.cpp.o -c /home/alexander/computer_science/projects/multithread_search/multithread_search/threads_manager.cpp

CMakeFiles/multithread_search.dir/threads_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multithread_search.dir/threads_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexander/computer_science/projects/multithread_search/multithread_search/threads_manager.cpp > CMakeFiles/multithread_search.dir/threads_manager.cpp.i

CMakeFiles/multithread_search.dir/threads_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multithread_search.dir/threads_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexander/computer_science/projects/multithread_search/multithread_search/threads_manager.cpp -o CMakeFiles/multithread_search.dir/threads_manager.cpp.s

# Object files for target multithread_search
multithread_search_OBJECTS = \
"CMakeFiles/multithread_search.dir/main.cpp.o" \
"CMakeFiles/multithread_search.dir/KMP.cpp.o" \
"CMakeFiles/multithread_search.dir/file_manager.cpp.o" \
"CMakeFiles/multithread_search.dir/threads_manager.cpp.o"

# External object files for target multithread_search
multithread_search_EXTERNAL_OBJECTS =

multithread_search: CMakeFiles/multithread_search.dir/main.cpp.o
multithread_search: CMakeFiles/multithread_search.dir/KMP.cpp.o
multithread_search: CMakeFiles/multithread_search.dir/file_manager.cpp.o
multithread_search: CMakeFiles/multithread_search.dir/threads_manager.cpp.o
multithread_search: CMakeFiles/multithread_search.dir/build.make
multithread_search: CMakeFiles/multithread_search.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexander/computer_science/projects/multithread_search/multithread_search/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable multithread_search"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multithread_search.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/multithread_search.dir/build: multithread_search

.PHONY : CMakeFiles/multithread_search.dir/build

CMakeFiles/multithread_search.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/multithread_search.dir/cmake_clean.cmake
.PHONY : CMakeFiles/multithread_search.dir/clean

CMakeFiles/multithread_search.dir/depend:
	cd /home/alexander/computer_science/projects/multithread_search/multithread_search/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexander/computer_science/projects/multithread_search/multithread_search /home/alexander/computer_science/projects/multithread_search/multithread_search /home/alexander/computer_science/projects/multithread_search/multithread_search/cmake-build-debug /home/alexander/computer_science/projects/multithread_search/multithread_search/cmake-build-debug /home/alexander/computer_science/projects/multithread_search/multithread_search/cmake-build-debug/CMakeFiles/multithread_search.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/multithread_search.dir/depend
