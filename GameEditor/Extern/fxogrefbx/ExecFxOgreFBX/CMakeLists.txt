project(ExecFxOgreFBX)

cmake_minimum_required(VERSION 2.8.10)
#set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
#cmake_policy(SET CMP0003 NEW)

set (CMAKE_PREFIX_PATH "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64" ${CMAKE_PREFIX_PATH})

# CMake policy introduced in relation to Qt 5.1
if("${CMAKE_VERSION}" VERSION_GREATER 2.8.11)   
cmake_policy(SET CMP0020 OLD)
endif()

set(SRCS_FILES
	./Src/stdafx.h
	./Src/targetver.h
	./Src/ExecFxOgreFBX.cpp
)

source_group("ExecFxOgreFBX" FILES ${SRCS_FILES})

set(BOOST_ROOT $ENV{BOOST_ROOT})
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost
			 1.57.0
			 COMPONENTS thread filesystem
			 REQUIRED)

# Create debug libraries with _d postfix
set(CMAKE_DEBUG_POSTFIX "_d")

# if we don't include this CMake will not include ui headers properly:
include_directories(./Src ../../tinyxml ../FxOgreFBX/Src ../../ogre/build/sdk/include/OGRE ../../ogre/build/sdk/include/OGRE/Animation "D:/ProgramFiles/Autodesk/FBX/FBX SDK/2016.1/include" ${Boost_INCLUDE_DIRS})

link_directories("D:/ProgramFiles/Autodesk/FBX/FBX SDK/2016.1/lib/vs2013/x64" ../../ogre/build/sdk/lib ${Boost_LIBRARY_DIRS})

ADD_DEFINITIONS(-DGAMEEDITOR_DLL)

set(ALLSRCS ${SRCS_FILES})

ADD_EXECUTABLE(ExecFxOgreFBX WIN32 ${ALLSRCS})

set_target_properties(ExecFxOgreFBX PROPERTIES DEBUG_POSTFIX _d LINK_FLAGS "/ENTRY:\"mainCRTStartup\"")

TARGET_LINK_LIBRARIES(ExecFxOgreFBX FxOgreFBX tinyxml libfbxsdk-md OgreMain_d)

add_dependencies(ExecFxOgreFBX FxOgreFBX tinyxml)