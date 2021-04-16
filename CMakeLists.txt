cmake_minimum_required(VERSION 3.0)
project(DRAWING_ROBOT)  
include_directories(include)
add_compile_options(-Wall -std=c++11 -O2)
# target_link_libraries(pthread)
# find_package(thread REQUIRED)
# find_package(RT REQUIRED)
# find_package(pigpio REQUIRED)
# Find the path to the pigpio includes.
find_path(pigpio_INCLUDE_DIR 
	NAMES pigpio.h pigpiod_if.h pigpiod_if2.h
	HINTS /usr/local/include)
	
# Find the pigpio libraries.
find_library(pigpio_LIBRARY 
	NAMES libpigpio.so
	HINTS /usr/local/lib)
find_library(pigpiod_if_LIBRARY 
	NAMES libpigpiod_if.so
	HINTS /usr/local/lib)
find_library(pigpiod_if2_LIBRARY 
	NAMES libpigpiod_if2.so
	HINTS /usr/local/lib)
    
# Set the pigpio variables to plural form to make them accessible for 
# the paramount cmake modules.
set(pigpio_INCLUDE_DIRS ${pigpio_INCLUDE_DIR})
set(pigpio_INCLUDES     ${pigpio_INCLUDE_DIR})

# Handle REQUIRED, QUIET, and version arguments 
# and set the <packagename>_FOUND variable.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(pigpio 
    DEFAULT_MSG 
    pigpio_INCLUDE_DIR pigpio_LIBRARY pigpiod_if_LIBRARY pigpiod_if2_LIBRARY)
find_package(thread REQUIRED)
set(CMAKE_CXX_FLAGES "${CMAKE_CXX_FLAGES} -wall")
set(CMAKE_BUILD_TYPE Debug)
add_executable(testmotor motor_test.cpp src/PiMotor.cpp)


