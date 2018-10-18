cmake_minimum_required(VERSION 3.4.1)

# building platform
if (${ANDROID_BUILD})
	message(STATUS "Building for Android Platform")
	message(STATUS "Android API level: ${ANDROID_PLATFORM_LEVEL}")
endif (${ANDROID_BUILD})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

if (${ANDROID_PLATFORM_LEVEL} LESS 12)
	message(FATAL_ERROR "GLES3 does not present with Android API level <= 11.")
	return()
elseif (${ANDROID_PLATFORM_LEVEL} LESS 18)
	message(STATUS "GLES3 will be dynamic initialized with Android API level 12 -> 17")
	add_definitions("-DDYNAMIC_ES3")
	set(OPENGL_LIB GLESv2)
else ()
	message(STATUS "Building using API level >= 18")
	set(OPENGL_LIB GLESv3)
endif (${ANDROID_PLATFORM_LEVEL} LESS 12)

add_subdirectory (../../calyx "${PROJECT_BINARY_DIR}/calyx")
add_subdirectory (../../clover "${PROJECT_BINARY_DIR}/clover")
add_subdirectory (../../floral "${PROJECT_BINARY_DIR}/floral")
add_subdirectory (../../helich "${PROJECT_BINARY_DIR}/helich")
add_subdirectory (../../imgui "${PROJECT_BINARY_DIR}/imgui")
add_subdirectory (../../insigne "${PROJECT_BINARY_DIR}/insigne")
add_subdirectory (../../lotus "${PROJECT_BINARY_DIR}/lotus")
add_subdirectory (../../refrain2 "${PROJECT_BINARY_DIR}/refrain2")
add_subdirectory (../../../prj/android_clang "${PROJECT_BINARY_DIR}/insigne_dev")

add_definitions(
	-D_CRT_SECURE_NO_WARNINGS)
	
if (${ANDROID_BUILD})
	message(STATUS "android will be built using Android configs")
	add_definitions (
		-DPLATFORM_POSIX)
		
	# platform abi
	if (${ANDROID_ABI} STREQUAL "arm64-v8a")
		message(STATUS "android Android ABI: arm64")
		add_definitions (
			-DPOSIX64)
	else ()
		message(STATUS "android Android ABI: arm")
		add_definitions (
			-DPOSIX32)
	endif (${ANDROID_ABI} STREQUAL "arm64-v8a")	
	
else ()
	message(STATUS "android will be built using Windows configs")
	add_definitions (
		-DPLATFORM_WINDOWS)
endif (${ANDROID_BUILD})

add_library(maincode SHARED
	"src/main/cpp/jnibridge.cpp")

# Include libraries needed for gles3jni lib
target_link_libraries(maincode
	insigne_dev
	floral
	helich
	clover
	refrain2
	calyx
	insigne
	${OPENGL_LIB}
	android
	log
	m)
