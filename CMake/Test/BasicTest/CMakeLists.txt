project(BasicTest)

cmake_minimum_required(VERSION 2.8.10)

file(GLOB SRCS_App_FILES Src/App/*.h Src/App/*.cpp)
source_group("Src\\App" FILES ${SRCS_App_FILES})

file(GLOB SRCS_Test_FILES Src/Test/*.h Src/Test/*.cpp)
source_group("Src\\Test" FILES ${SRCS_Test_FILES})

include_directories(Src Src/App Src/Test)

#ADD_DEFINITIONS(-DTEST)

set(ALL_SRCS ${SRCS_App_FILES} ${SRCS_Test_FILES})

ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${ALL_SRCS})

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX LINK_FLAGS "/SUBSYSTEM:\"CONSOLE\"")