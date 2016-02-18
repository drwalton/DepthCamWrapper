find_path(KINECT18_INCLUDE_DIRS
	NAMES
		NuiApi.h
	PATHS
		"C:/Program Files/Microsoft SDKs/Kinect/v1.8/inc"
)

find_library(KINECT18_LIBRARIES
	NAMES
		Kinect10.lib
	PATHS
		"C:/Program Files/Microsoft SDKs/Kinect/v1.8/lib/x86"
)

