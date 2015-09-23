set (PROJECT_NAME AStar)
project(${PROJECT_NAME})

cmake_minimum_required(VERSION 2.8.10)
#set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
#cmake_policy(SET CMP0003 NEW)

if(MSVC)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DNOMINMAX)
endif(MSVC)

#set (CMAKE_MODULE_PATH "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64")
set (CMAKE_PREFIX_PATH "F:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64" ${CMAKE_PREFIX_PATH})

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "install prefix" FORCE)

# CMake policy introduced in relation to Qt 5.1
if("${CMAKE_VERSION}" VERSION_GREATER 2.8.11)   
	cmake_policy(SET CMP0020 OLD)
endif()

set(SRCS_FILES
	./MDijkstra.cpp
	./MGraph.h
	./MGraph.cpp
	./Test.cpp
)

source_group("Src" FILES ${SRCS_FILES})

# Create debug libraries with _d postfix
set(CMAKE_DEBUG_POSTFIX "_d")

# if we don't include this CMake will not include ui headers properly:
#include_directories(${CMAKE_CURRENT_BINARY_DIR})
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)

include_directories(.)
#include_directories(${QT_BINARY_DIR}/../include)

#link_directories(${QT_BINARY_DIR}/../lib)

set(ALLSRCS ${SRCS_FILES})

ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${ALLSRCS})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d LINK_FLAGS "/ENTRY:\"mainCRTStartup\"")

#TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES})