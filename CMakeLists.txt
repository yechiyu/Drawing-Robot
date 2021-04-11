cmake_minimum_required(VERSION 3.0)
project(DRAWINGPI)  
include_directories(include)
set(CMAKE_CXX_FLAGES "${CMAKE_CXX_FLAGES} -wall")
set(CMAKE_BUILD_TYPE Debug)
add_executable(main_camke main.cpp src/pid_motor.cpp)

