find_path(OPENCV_INCLUDE_DIRS
	NAMES
		opencv2/opencv.hpp
	PATHS
		"C:/local/opencv/opencv-2.4.11/build/install/include"
		/opt/local/include
		/usr/local/include
)

if(NOT ${OPENCV_INCLUDE_DIRS} EQUAL OPENCV_INCLUDE_DIRS-NOTFOUND)
	set(OPENCV_FOUND TRUE)
endif(NOT ${OPENCV_INCLUDE_DIRS} EQUAL OPENCV_INCLUDE_DIRS-NOTFOUND)

set(LIB_PATHS
		"C:/local/opencv/opencv-2.4.11/build/install/x86/vc12/lib"
		/opt/local/lib
		/usr/local/lib
)

find_library(OPENCV_CALIB3D_LIBRARY
	NAMES
		opencv_calib3d2411
		opencv_calib3d
	PATHS
		${LIB_PATHS}
)
find_library(OPENCV_CORE_LIBRARY
	NAMES
		opencv_core
		opencv_core2411
	PATHS
		${LIB_PATHS}
)
find_library(OPENCV_FEATURES2D_LIBRARY
	NAMES
		opencv_features2d
		opencv_features2d2411
	PATHS
		${LIB_PATHS}
)
find_library(OPENCV_FLANN_LIBRARY
	NAMES
		opencv_flann
		opencv_flann2411
	PATHS
		${LIB_PATHS}
)
find_library(OPENCV_HIGHGUI_LIBRARY
	NAMES
		opencv_highgui
		opencv_highgui2411
	PATHS
		${LIB_PATHS}
)
find_library(OPENCV_IMGPROC_LIBRARY
	NAMES
		opencv_imgproc
		opencv_imgproc2411
	PATHS
		${LIB_PATHS}
)

set(OPENCV_LIBRARIES
	${OPENCV_CALIB3D_LIBRARY}
	${OPENCV_CORE_LIBRARY}
	${OPENCV_FEATURES2D_LIBRARY}
	${OPENCV_FLANN_LIBRARY}
	${OPENCV_HIGHGUI_LIBRARY}
	${OPENCV_IMGPROC_LIBRARY}
)
