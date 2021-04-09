cmake_minimum_required(VERSION 3.0)
project(DRAWINGPI)  
include_directories(include)
add_executable(main_camke main.cpp src/pid_motor.cpp)