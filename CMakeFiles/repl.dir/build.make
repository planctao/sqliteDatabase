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
CMAKE_SOURCE_DIR = /home/sqlite_db

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sqlite_db

# Include any dependencies generated for this target.
include CMakeFiles/repl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/repl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/repl.dir/flags.make

CMakeFiles/repl.dir/execute.c.o: CMakeFiles/repl.dir/flags.make
CMakeFiles/repl.dir/execute.c.o: execute.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sqlite_db/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/repl.dir/execute.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/repl.dir/execute.c.o   -c /home/sqlite_db/execute.c

CMakeFiles/repl.dir/execute.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/repl.dir/execute.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sqlite_db/execute.c > CMakeFiles/repl.dir/execute.c.i

CMakeFiles/repl.dir/execute.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/repl.dir/execute.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sqlite_db/execute.c -o CMakeFiles/repl.dir/execute.c.s

CMakeFiles/repl.dir/repl.c.o: CMakeFiles/repl.dir/flags.make
CMakeFiles/repl.dir/repl.c.o: repl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sqlite_db/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/repl.dir/repl.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/repl.dir/repl.c.o   -c /home/sqlite_db/repl.c

CMakeFiles/repl.dir/repl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/repl.dir/repl.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sqlite_db/repl.c > CMakeFiles/repl.dir/repl.c.i

CMakeFiles/repl.dir/repl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/repl.dir/repl.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sqlite_db/repl.c -o CMakeFiles/repl.dir/repl.c.s

CMakeFiles/repl.dir/row.c.o: CMakeFiles/repl.dir/flags.make
CMakeFiles/repl.dir/row.c.o: row.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sqlite_db/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/repl.dir/row.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/repl.dir/row.c.o   -c /home/sqlite_db/row.c

CMakeFiles/repl.dir/row.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/repl.dir/row.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sqlite_db/row.c > CMakeFiles/repl.dir/row.c.i

CMakeFiles/repl.dir/row.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/repl.dir/row.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sqlite_db/row.c -o CMakeFiles/repl.dir/row.c.s

CMakeFiles/repl.dir/table.c.o: CMakeFiles/repl.dir/flags.make
CMakeFiles/repl.dir/table.c.o: table.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sqlite_db/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/repl.dir/table.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/repl.dir/table.c.o   -c /home/sqlite_db/table.c

CMakeFiles/repl.dir/table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/repl.dir/table.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sqlite_db/table.c > CMakeFiles/repl.dir/table.c.i

CMakeFiles/repl.dir/table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/repl.dir/table.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sqlite_db/table.c -o CMakeFiles/repl.dir/table.c.s

# Object files for target repl
repl_OBJECTS = \
"CMakeFiles/repl.dir/execute.c.o" \
"CMakeFiles/repl.dir/repl.c.o" \
"CMakeFiles/repl.dir/row.c.o" \
"CMakeFiles/repl.dir/table.c.o"

# External object files for target repl
repl_EXTERNAL_OBJECTS =

repl: CMakeFiles/repl.dir/execute.c.o
repl: CMakeFiles/repl.dir/repl.c.o
repl: CMakeFiles/repl.dir/row.c.o
repl: CMakeFiles/repl.dir/table.c.o
repl: CMakeFiles/repl.dir/build.make
repl: CMakeFiles/repl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sqlite_db/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable repl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/repl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/repl.dir/build: repl

.PHONY : CMakeFiles/repl.dir/build

CMakeFiles/repl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/repl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/repl.dir/clean

CMakeFiles/repl.dir/depend:
	cd /home/sqlite_db && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sqlite_db /home/sqlite_db /home/sqlite_db /home/sqlite_db /home/sqlite_db/CMakeFiles/repl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/repl.dir/depend

