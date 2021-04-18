cmake_minimum_required(VERSION 3.0)
project(DRAWING_ROBOT)  

add_executable(testmotor src/mainTest.cpp)

add_library(PiMotor src/PiMotor.cpp)

target_include_directories(testmotor PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Threads REQUIRED)
target_link_libraries(testmotor PUBLIC
	${CMAKE_THREAD_LIBS_INIT}
	pigpio
	PiMotor
)

add_compile_options(-Wall -std=c++11 -O2)
# target_link_libraries(pthread)


set(CMAKE_CXX_FLAGES "${CMAKE_CXX_FLAGES} -wall")
set(CMAKE_BUILD_TYPE Debug)



