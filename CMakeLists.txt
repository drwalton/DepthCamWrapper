cmake_minimum_required(VERSION 3.5)

project(DepthCamWrapper CXX)

set(PROJECT_BINARY_DIR bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(OpenNI2)
find_package(Kinect18)

include_directories(${OPENNI2_INCLUDE_DIRS})
if(WIN32)
	include_directories(${KINECT18_INCLUDE_DIRS})
endif(WIN32)

include_directories(include)
add_subdirectory(src)

