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
CMAKE_SOURCE_DIR = /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/build_ARM

# Include any dependencies generated for this target.
include src/CMakeFiles/4_sysconf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/4_sysconf.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/4_sysconf.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/4_sysconf.dir/flags.make

src/CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.o: src/CMakeFiles/4_sysconf.dir/flags.make
src/CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.o: ../src/4_sysconf_Test.c
src/CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.o: src/CMakeFiles/4_sysconf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/build_ARM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.o"
	cd /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/build_ARM/src && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.o -MF CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.o.d -o CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.o -c /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/src/4_sysconf_Test.c

src/CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.i"
	cd /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/build_ARM/src && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/src/4_sysconf_Test.c > CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.i

src/CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.s"
	cd /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/build_ARM/src && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/src/4_sysconf_Test.c -o CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.s

# Object files for target 4_sysconf
4_sysconf_OBJECTS = \
"CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.o"

# External object files for target 4_sysconf
4_sysconf_EXTERNAL_OBJECTS =

bin/4_sysconf: src/CMakeFiles/4_sysconf.dir/4_sysconf_Test.c.o
bin/4_sysconf: src/CMakeFiles/4_sysconf.dir/build.make
bin/4_sysconf: src/CMakeFiles/4_sysconf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/build_ARM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/4_sysconf"
	cd /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/build_ARM/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/4_sysconf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/4_sysconf.dir/build: bin/4_sysconf
.PHONY : src/CMakeFiles/4_sysconf.dir/build

src/CMakeFiles/4_sysconf.dir/clean:
	cd /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/build_ARM/src && $(CMAKE_COMMAND) -P CMakeFiles/4_sysconf.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/4_sysconf.dir/clean

src/CMakeFiles/4_sysconf.dir/depend:
	cd /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/build_ARM && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/src /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/build_ARM /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/build_ARM/src /mnt/c/Users/kille/OneDrive/桌面/Linux_C_APP/7_Kernel_Message/build_ARM/src/CMakeFiles/4_sysconf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/4_sysconf.dir/depend

