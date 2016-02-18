add_library(DepthCamWrapper
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

target_link_libraries(DepthCamWrapper ${LIBS})

