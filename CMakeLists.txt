cmake_minimum_required(VERSION 3.5)

project(DepthCamWrapper CXX)

set(CMAKE_BINARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(OpenNI2 REQUIRED)
find_package(Kinect18)
find_package(OpenCV)

include_directories(${OPENNI2_INCLUDE_DIRS})
if(WIN32)
	include_directories(${KINECT18_INCLUDE_DIRS})
endif(WIN32)

include_directories(include)
add_subdirectory(src)

