cmake_minimum_required(VERSION 2.6)

cmake_policy(SET CMP0003 NEW)
cmake_policy(SET CMP0005 NEW)

project(FileArchiveTool)

message(STATUS "builder main start")

set(CMAKE_DEBUG_POSTFIX "_d")

# 这样设置 CMAKE_INSTALL_PREFIX 是不行的
# set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})
# 需要这样设置
if (WIN32 OR APPLE)
  if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # We don't want to install in default system location, install is really for the SDK, so call it that
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "install prefix" FORCE)
  endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif(WIN32 OR APPLE)

# if(MSVC)
if(MSVC)
	message(STATUS "Setting Visual Studio 2005+ option /MP to ${OGITOR_MSVC_ENABLE_MP}")
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DNOMINMAX)
endif(MSVC)

add_subdirectory(FileArchiveTool)
add_subdirectory(QtFileArchiveTool)
add_subdirectory(lzma920)

install(FILES 
	${CMAKE_SOURCE_DIR}/icu4c-54_1-src/bin64/icuuc54d.dll
	DESTINATION "${QtFileArchiveTool_BINARY_DIR}/Debug/" CONFIGURATIONS Debug
)
install(FILES 
	${CMAKE_SOURCE_DIR}/icu4c-54_1-src/bin64/icuuc54.dll
	DESTINATION "${QtFileArchiveTool_BINARY_DIR}/Release" CONFIGURATIONS Release None ""
)

install(FILES 
	${CMAKE_SOURCE_DIR}/icu4c-54_1-src/bin64/icudt54.dll
	DESTINATION "${QtFileArchiveTool_BINARY_DIR}/Debug/" CONFIGURATIONS Debug
)
install(FILES 
	${CMAKE_SOURCE_DIR}/icu4c-54_1-src/bin64/icudt54.dll
	DESTINATION "${QtFileArchiveTool_BINARY_DIR}/Release" CONFIGURATIONS Release None ""
)