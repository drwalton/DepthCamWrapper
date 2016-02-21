set(WIN32_PATHS "C:/Program Files (x86)/OpenNI2/Include")

set(PATHS /usr/local/include /opt/local/include ~/lib/openni2/include)

if(WIN32)
	set(PATHS ${PATHS} ${WIN32_PATHS})
endif(WIN32)

find_path(OPENNI2_INCLUDE_DIRS
	NAMES
		OpenNI.h
	PATHS
		${PATHS}
)

if(NOT ${OPENNI2_INCLUDE_DIRS} EQUAL OPENNI2_INCLUDE_DIRS-NOTFOUND)
	set(OPENNI2_FOUND TRUE)
endif(NOT ${OPENNI2_INCLUDE_DIRS} EQUAL OPENNI2_INCLUDE_DIRS-NOTFOUND)

set(LIB_PATHS /usr/local/lib /opt/local/lib ~/lib/openni2/Bin/x64-Release)

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

message("OpenNI2 Lib Found: ${OPENNI2_LIBRARIES}")

