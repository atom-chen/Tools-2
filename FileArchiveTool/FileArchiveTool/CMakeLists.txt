project(FileArchiveTool)

cmake_minimum_required(VERSION 2.8.10)
#set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
#cmake_policy(SET CMP0003 NEW)

set (CMAKE_PREFIX_PATH "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64" ${CMAKE_PREFIX_PATH})

# CMake policy introduced in relation to Qt 5.1
if("${CMAKE_VERSION}" VERSION_GREATER 2.8.11)   
	cmake_policy(SET CMP0020 OLD)
endif()

file(GLOB SRCS_FILES Src/*.h Src/*.cpp)

source_group("Source Files" FILES ${SRCS_FILES})

set(BOOST_ROOT $ENV{BOOST_ROOT})
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost
             1.57.0
             COMPONENTS thread
             REQUIRED)

include_directories(./Src ../libiconv-1.9.2-1-lib/include ../FastDelegate_src ${Boost_INCLUDE_DIRS} ../lzma920/C)
link_directories(../libiconv-1.9.2-1-lib/lib ${Boost_LIBRARY_DIRS})

ADD_DEFINITIONS(-DFILEARCHIVETOOL_DLL -DFILEARCHIVETOOL_DLL_EXPORT)

set(ALL_SRCS ${SRCS_FILES} ${INCS_FILES})

ADD_LIBRARY(FileArchiveTool SHARED ${ALL_SRCS})

set_target_properties(FileArchiveTool PROPERTIES DEBUG_POSTFIX _d)

TARGET_LINK_LIBRARIES(FileArchiveTool libiconv)

add_dependencies(FileArchiveTool LzmaLib)

install(FILES 
	${FileArchiveTool_BINARY_DIR}/Debug/FileArchiveTool_d.dll
	DESTINATION "${FileArchiveTool_BINARY_DIR}/../QtFileArchiveTool/Debug" CONFIGURATIONS Debug
)
install(FILES 
	${FileArchiveTool_BINARY_DIR}/Release/FileArchiveTool.dll
	DESTINATION "${FileArchiveTool_BINARY_DIR}/../QtFileArchiveTool/Release" CONFIGURATIONS Release None ""
)
install(FILES 
	${FileArchiveTool_BINARY_DIR}/RelWithDebInfo/FileArchiveTool.dll
	DESTINATION "${FileArchiveTool_BINARY_DIR}/../QtFileArchiveTool/RelWithDebInfo" CONFIGURATIONS RelWithDebInfo
)
install(FILES 
	${FileArchiveTool_BINARY_DIR}/MinSizeRel/FileArchiveTool.dll
	DESTINATION "${FileArchiveTool_BINARY_DIR}/../QtFileArchiveTool/MinSizeRel" CONFIGURATIONS MinSizeRel
)