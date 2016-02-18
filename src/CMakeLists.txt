add_library(DepthCamWrapper STATIC
	../include/DepthCam.hpp
	../include/KinectDepthCam.hpp
	../include/OpenNiDepthCam.hpp

	DepthCam.cpp
	KinectDepthCam.cpp
	OpenNiDepthCam.cpp
)

set(LIBS ${OPENNI2_LIBRARIES})

if(WIN32)
	set(LIBS ${LIBS} ${KINECT18_LIBRARIES})
endif(WIN32)

message("ONI2LIBS ${OPENNI2_LIBRARIES}")
target_link_libraries(DepthCamWrapper ${OPENNI2_LIBRARIES})

if(OPENCV_FOUND)
	include_directories(${OPENCV_INCLUDE_DIRS})
	add_executable(DepthCamViewer DepthCamViewer.cpp)
	target_link_libraries(DepthCamViewer DepthCamWrapper ${LIBS} ${OPENCV_LIBRARIES})
endif(OPENCV_FOUND)

