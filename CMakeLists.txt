cmake_minimum_required(VERSION 3.0)
project(DRAWINGPI)  
include_directories(include)
set(CMAKE_CXX_FLAGES "${CMAKE_CXX_FLAGES} -wall")
set(CMAKE_BUILD_TYPE Debug)
add_executable(my_camke_exe main.cpp src/rotary_encoder.cpp src/test_rotary_encoder.cpp)

