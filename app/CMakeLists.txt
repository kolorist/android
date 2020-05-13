cmake_minimum_required (VERSION 3.0)

project ("android-pal")

include_directories ("${PROJECT_SOURCE_DIR}/src/main/cpp")

set (file_list
	"${PROJECT_SOURCE_DIR}/src/main/cpp/jnibridge.cpp"
	)

set (lib_list
	calyx
	android
	log
	m)

add_library (${PROJECT_NAME} ${file_list})

target_link_libraries (${PROJECT_NAME}
	${lib_list})
	
target_compile_options(${PROJECT_NAME}
	PRIVATE	$<$<COMPILE_LANGUAGE:CXX>:-std=c++11 -Wall -fno-rtti -fno-exceptions>)

# target_include_directories (${PROJECT_NAME} PUBLIC
	# $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp>)