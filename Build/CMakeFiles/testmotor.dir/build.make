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
CMAKE_SOURCE_DIR = /home/pi/Drawing-Robot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Drawing-Robot/Build

# Include any dependencies generated for this target.
include CMakeFiles/testmotor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testmotor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testmotor.dir/flags.make

CMakeFiles/testmotor.dir/motor_test.cpp.o: CMakeFiles/testmotor.dir/flags.make
CMakeFiles/testmotor.dir/motor_test.cpp.o: ../motor_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Drawing-Robot/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testmotor.dir/motor_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testmotor.dir/motor_test.cpp.o -c /home/pi/Drawing-Robot/motor_test.cpp

CMakeFiles/testmotor.dir/motor_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmotor.dir/motor_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Drawing-Robot/motor_test.cpp > CMakeFiles/testmotor.dir/motor_test.cpp.i

CMakeFiles/testmotor.dir/motor_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmotor.dir/motor_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Drawing-Robot/motor_test.cpp -o CMakeFiles/testmotor.dir/motor_test.cpp.s

CMakeFiles/testmotor.dir/src/PiMotor.cpp.o: CMakeFiles/testmotor.dir/flags.make
CMakeFiles/testmotor.dir/src/PiMotor.cpp.o: ../src/PiMotor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Drawing-Robot/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testmotor.dir/src/PiMotor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testmotor.dir/src/PiMotor.cpp.o -c /home/pi/Drawing-Robot/src/PiMotor.cpp

CMakeFiles/testmotor.dir/src/PiMotor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testmotor.dir/src/PiMotor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Drawing-Robot/src/PiMotor.cpp > CMakeFiles/testmotor.dir/src/PiMotor.cpp.i

CMakeFiles/testmotor.dir/src/PiMotor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testmotor.dir/src/PiMotor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Drawing-Robot/src/PiMotor.cpp -o CMakeFiles/testmotor.dir/src/PiMotor.cpp.s

# Object files for target testmotor
testmotor_OBJECTS = \
"CMakeFiles/testmotor.dir/motor_test.cpp.o" \
"CMakeFiles/testmotor.dir/src/PiMotor.cpp.o"

# External object files for target testmotor
testmotor_EXTERNAL_OBJECTS =

testmotor: CMakeFiles/testmotor.dir/motor_test.cpp.o
testmotor: CMakeFiles/testmotor.dir/src/PiMotor.cpp.o
testmotor: CMakeFiles/testmotor.dir/build.make
testmotor: CMakeFiles/testmotor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Drawing-Robot/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable testmotor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testmotor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testmotor.dir/build: testmotor

.PHONY : CMakeFiles/testmotor.dir/build

CMakeFiles/testmotor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testmotor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testmotor.dir/clean

CMakeFiles/testmotor.dir/depend:
	cd /home/pi/Drawing-Robot/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Drawing-Robot /home/pi/Drawing-Robot /home/pi/Drawing-Robot/Build /home/pi/Drawing-Robot/Build /home/pi/Drawing-Robot/Build/CMakeFiles/testmotor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testmotor.dir/depend
