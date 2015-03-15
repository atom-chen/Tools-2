set(LIBRARY_NAME 3dsMaxPluginInfo)

cmake_policy(SET CMP0043 NEW)

file(GLOB LIBRARY_SRCS *.h *.cpp)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(WIN32)
	add_executable(${LIBRARY_NAME} WIN32 ${LIBRARY_SRCS})
endif()

set_target_properties(${LIBRARY_NAME} PROPERTIES DEBUG_POSTFIX _d LINK_FLAGS "/SUBSYSTEM:\"CONSOLE\"")