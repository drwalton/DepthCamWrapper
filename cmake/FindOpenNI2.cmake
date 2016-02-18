set(WIN32_PATHS "C:/Program Files (x86)/OpenNI2/Include")

set(PATHS)

if(WIN32)
	set(PATHS ${PATHS} ${WIN32_PATHS})
endif(WIN32)

find_path(OPENNI2_INCLUDE_DIRS
	NAMES
		OpenNI.h
	PATHS
		${PATHS}
)

set(LIB_PATHS)

if(WIN32)
	set(LIB_PATHS ${LIB_PATHS}
		"C:/Program Files (x86)/OpenNI2/Lib")
endif(WIN32)

find_library(OPENNI2_LIBRARIES
	NAMES
		OpenNI2
	PATHS
		${LIB_PATHS}
)

