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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/build"

# Include any dependencies generated for this target.
include CMakeFiles/fork.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fork.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fork.dir/flags.make

CMakeFiles/fork.dir/fork.c.o: CMakeFiles/fork.dir/flags.make
CMakeFiles/fork.dir/fork.c.o: ../fork.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/fork.dir/fork.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/fork.dir/fork.c.o   -c "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/fork.c"

CMakeFiles/fork.dir/fork.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fork.dir/fork.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/fork.c" > CMakeFiles/fork.dir/fork.c.i

CMakeFiles/fork.dir/fork.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fork.dir/fork.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/fork.c" -o CMakeFiles/fork.dir/fork.c.s

CMakeFiles/fork.dir/pomiar_czasu.c.o: CMakeFiles/fork.dir/flags.make
CMakeFiles/fork.dir/pomiar_czasu.c.o: ../pomiar_czasu.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/fork.dir/pomiar_czasu.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/fork.dir/pomiar_czasu.c.o   -c "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/pomiar_czasu.c"

CMakeFiles/fork.dir/pomiar_czasu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fork.dir/pomiar_czasu.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/pomiar_czasu.c" > CMakeFiles/fork.dir/pomiar_czasu.c.i

CMakeFiles/fork.dir/pomiar_czasu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fork.dir/pomiar_czasu.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/pomiar_czasu.c" -o CMakeFiles/fork.dir/pomiar_czasu.c.s

# Object files for target fork
fork_OBJECTS = \
"CMakeFiles/fork.dir/fork.c.o" \
"CMakeFiles/fork.dir/pomiar_czasu.c.o"

# External object files for target fork
fork_EXTERNAL_OBJECTS =

fork: CMakeFiles/fork.dir/fork.c.o
fork: CMakeFiles/fork.dir/pomiar_czasu.c.o
fork: CMakeFiles/fork.dir/build.make
fork: CMakeFiles/fork.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable fork"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fork.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fork.dir/build: fork

.PHONY : CMakeFiles/fork.dir/build

CMakeFiles/fork.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fork.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fork.dir/clean

CMakeFiles/fork.dir/depend:
	cd "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2" "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2" "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/build" "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/build" "/mnt/w/Studia/semestr 6/Przetwarzanie wspolbierzne/labs/2/build/CMakeFiles/fork.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/fork.dir/depend

