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
CMAKE_SOURCE_DIR = /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/build_ARM

# Include any dependencies generated for this target.
include src/CMakeFiles/5_pthread_setcancelstateFunc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/5_pthread_setcancelstateFunc.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/5_pthread_setcancelstateFunc.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/5_pthread_setcancelstateFunc.dir/flags.make

src/CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.o: src/CMakeFiles/5_pthread_setcancelstateFunc.dir/flags.make
src/CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.o: ../src/5_pthread_setcancelstate_Test.c
src/CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.o: src/CMakeFiles/5_pthread_setcancelstateFunc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/build_ARM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.o"
	cd /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/build_ARM/src && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.o -MF CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.o.d -o CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.o -c /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/src/5_pthread_setcancelstate_Test.c

src/CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.i"
	cd /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/build_ARM/src && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/src/5_pthread_setcancelstate_Test.c > CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.i

src/CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.s"
	cd /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/build_ARM/src && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/src/5_pthread_setcancelstate_Test.c -o CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.s

# Object files for target 5_pthread_setcancelstateFunc
5_pthread_setcancelstateFunc_OBJECTS = \
"CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.o"

# External object files for target 5_pthread_setcancelstateFunc
5_pthread_setcancelstateFunc_EXTERNAL_OBJECTS =

bin/5_pthread_setcancelstateFunc: src/CMakeFiles/5_pthread_setcancelstateFunc.dir/5_pthread_setcancelstate_Test.c.o
bin/5_pthread_setcancelstateFunc: src/CMakeFiles/5_pthread_setcancelstateFunc.dir/build.make
bin/5_pthread_setcancelstateFunc: src/CMakeFiles/5_pthread_setcancelstateFunc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/build_ARM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/5_pthread_setcancelstateFunc"
	cd /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/build_ARM/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/5_pthread_setcancelstateFunc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/5_pthread_setcancelstateFunc.dir/build: bin/5_pthread_setcancelstateFunc
.PHONY : src/CMakeFiles/5_pthread_setcancelstateFunc.dir/build

src/CMakeFiles/5_pthread_setcancelstateFunc.dir/clean:
	cd /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/build_ARM/src && $(CMAKE_COMMAND) -P CMakeFiles/5_pthread_setcancelstateFunc.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/5_pthread_setcancelstateFunc.dir/clean

src/CMakeFiles/5_pthread_setcancelstateFunc.dir/depend:
	cd /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/build_ARM && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/src /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/build_ARM /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/build_ARM/src /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/11_Thread/build_ARM/src/CMakeFiles/5_pthread_setcancelstateFunc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/5_pthread_setcancelstateFunc.dir/depend

