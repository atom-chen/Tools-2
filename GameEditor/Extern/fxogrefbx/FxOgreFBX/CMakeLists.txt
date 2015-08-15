project(FxOgreFBX)

cmake_minimum_required(VERSION 2.8.10)
#set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
#cmake_policy(SET CMP0003 NEW)

set (CMAKE_PREFIX_PATH "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64" ${CMAKE_PREFIX_PATH})

# CMake policy introduced in relation to Qt 5.1
if("${CMAKE_VERSION}" VERSION_GREATER 2.8.11)   
	cmake_policy(SET CMP0020 OLD)
endif()

set(SRCS_FILES
	./Src/animation.h
	./Src/blendshape.cpp
	./Src/blendshape.h
	./Src/common.cpp
	./Src/common.h
	./Src/FBXSDKCommon.h
	./Src/FxOgreFBXDLL.cpp
	./Src/FxOgreFBXDLL.h
	./Src/FxOgreFBXLog.cpp
	./Src/FxOgreFBXLog.h
	./Src/material.cpp
	./Src/material.h
	./Src/materialSet.cpp
	./Src/materialSet.h
	./Src/mesh.cpp
	./Src/mesh.h
	./Src/ogreExporter.cpp
	./Src/ogreExporter.h
	./Src/paramlist.cpp
	./Src/paramlist.h
	./Src/scene.cpp
	./Src/scene.h
	./Src/skeleton.cpp
	./Src/skeleton.h
	./Src/submesh.cpp
	./Src/submesh.h
	./Src/vertex.h
	./Src/xmlsupport.cpp
	./Src/xmlsupport.h
	./Src/_singleton.h
)

source_group("FxOgreFBX" FILES ${SRCS_FILES})

set(BOOST_ROOT $ENV{BOOST_ROOT})
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost
			 1.57.0
			 COMPONENTS thread filesystem
			 REQUIRED)

# Create debug libraries with _d postfix
set(CMAKE_DEBUG_POSTFIX "_d")

include_directories(./Src ../../tinyxml ../../ogre/build/sdk/include/OGRE ../../ogre/build/sdk/include/OGRE/Animation "D:/ProgramFiles/Autodesk/FBX/FBX SDK/2016.1/include" ${Boost_INCLUDE_DIRS})
link_directories("D:/ProgramFiles/Autodesk/FBX/FBX SDK/2016.1/lib/vs2013/x64" ../../ogre/build/sdk/lib ${Boost_LIBRARY_DIRS})

ADD_DEFINITIONS(-DGAMEEDITOR_DLL -DGAMEEDITOR_DLL_EXPORT)

set(ALL_SRCS ${SRCS_FILES})

ADD_LIBRARY(FxOgreFBX SHARED ${ALL_SRCS})

set_target_properties(FxOgreFBX PROPERTIES DEBUG_POSTFIX _d)

TARGET_LINK_LIBRARIES(FxOgreFBX tinyxml libfbxsdk-md OgreMain_d)

add_dependencies(FxOgreFBX tinyxml)

install(FILES 
	${FxOgreFBX_BINARY_DIR}/Debug/FxOgreFBX_d.dll
	DESTINATION "${FxOgreFBX_BINARY_DIR}/../ExecFxOgreFBX/Debug" CONFIGURATIONS Debug
)
install(FILES 
	${FxOgreFBX_BINARY_DIR}/Release/FxOgreFBX.dll
	DESTINATION "${FxOgreFBX_BINARY_DIR}/../ExecFxOgreFBX/Release" CONFIGURATIONS Release None ""
)
install(FILES 
	${FxOgreFBX_BINARY_DIR}/RelWithDebInfo/FxOgreFBX.dll
	DESTINATION "${FxOgreFBX_BINARY_DIR}/../ExecFxOgreFBX/RelWithDebInfo" CONFIGURATIONS RelWithDebInfo
)
install(FILES 
	${FxOgreFBX_BINARY_DIR}/MinSizeRel/FxOgreFBX.dll
	DESTINATION "${FxOgreFBX_BINARY_DIR}/../ExecFxOgreFBX/MinSizeRel" CONFIGURATIONS MinSizeRel
)