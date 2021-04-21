cmake_minimum_required(VERSION 3.0)
project(DRAWING_ROBOT)  

add_executable(mainTest src/mainTest.cpp)

add_library(PiMotor src/PiMotor.cpp)
add_library(reDecoder src/reDecoder.cpp)
add_library(controlMotor src/controlMotor.cpp src/PiMotor.cpp src/reDecoder.cpp)
add_library(calPosition src/calPosition.cpp)
add_library(movetoTarget src/movetoTarget.cpp)
add_library(processImages src/processImages.cpp)
add_library(pixtoMeter src/pixtoMeter.cpp)

target_include_directories(mainTest PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}/include)
target_link_libraries( processImages ${OpenCV_LIBS})

find_package(Threads REQUIRED)
target_link_libraries(mainTest PUBLIC
	${CMAKE_THREAD_LIBS_INIT}
	pigpio
	PiMotor
	reDecoder
	controlMotor
	calPosition
	movetoTarget
	processImages
	pixtoMeter
)

add_compile_options(-Wall -std=c++11 -O2)
# target_link_libraries(pthread)


set(CMAKE_CXX_FLAGES "${CMAKE_CXX_FLAGES} -wall")
set(CMAKE_BUILD_TYPE Debug)

# cmake_minimum_required(VERSION 3.0)
# project(DRAWING_ROBOT)  

# add_executable(imagetest src/processImages.cpp)
# add_library(processImages src/processImages.cpp)
# target_include_directories(processImages PUBLIC
# 	${CMAKE_CURRENT_SOURCE_DIR}/include)
# target_link_libraries(imagetest PUBLIC
# 	${CMAKE_THREAD_LIBS_INIT}
	
# 	processImages
# )
# find_package(OpenCV REQUIRED)
# include_directories(${OpenCV_INCLUDE_DIRS}/include)
# target_link_libraries( processImages ${OpenCV_LIBS})
# add_compile_options(-Wall -std=c++11 -O2)

# set(CMAKE_CXX_FLAGES "${CMAKE_CXX_FLAGES} -wall")
# set(CMAKE_BUILD_TYPE Debug)