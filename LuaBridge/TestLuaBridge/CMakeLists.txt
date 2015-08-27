set (PROJECT_NAME TestLuaBridge)
project(${PROJECT_NAME})
cmake_minimum_required(VERSION 3.0.0)

set (CMAKE_PREFIX_PATH "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64" ${CMAKE_PREFIX_PATH})

SET(SRC_FILES
	./TestsMain.cpp
	./Tests.h
	./Tests.cpp
	./Performance.h
	./Performance.cpp
)

source_group("Src" FILES ${SRC_FILES})
include_directories(. ../lua ../LuaBridge)
#link_directories(Lua)
set(ALLSRCS ${SRC_FILES})

ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${ALLSRCS})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d LINK_FLAGS "/ENTRY:\"mainCRTStartup\"")

TARGET_LINK_LIBRARIES(${PROJECT_NAME} Lua)

add_dependencies(${PROJECT_NAME} Lua)