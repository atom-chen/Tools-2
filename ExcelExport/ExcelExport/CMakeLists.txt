cmake_minimum_required(VERSION 2.6)

cmake_policy(SET CMP0003 NEW)
cmake_policy(SET CMP0005 NEW)

project(ExcelExport)

message(STATUS "builder main start")

if (WIN32 OR APPLE)
  if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # We don't want to install in default system location, install is really for the SDK, so call it that
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "install prefix" FORCE)
  endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif(WIN32 OR APPLE)

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})

if(MSVC11 OR MSVC12)
	message(STATUS "Setting Visual Studio 2005+ option /MP to ${OGITOR_MSVC_ENABLE_MP}")
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DNOMINMAX)
endif(MSVC11 OR MSVC12)

add_subdirectory(tinyxml)
add_subdirectory(QtExcelExport)
#add_subdirectory(Extern)

install(FILES 
	${CMAKE_SOURCE_DIR}/QtExcelExport/Config/Config.xml DESTINATION "${CMAKE_BINARY_DIR}/QtExcelExport"
)