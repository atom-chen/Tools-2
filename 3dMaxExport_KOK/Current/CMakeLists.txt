cmake_minimum_required(VERSION 2.8)

project(maxawd)
set(MAXAWD_VERSION 0.17)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_SOURCE_DIR}/cmake
)

if (WIN32 OR APPLE)
  if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # We don't want to install in default system location, install is really for the SDK, so call it that
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "install prefix" FORCE)
  endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif(WIN32 OR APPLE)

option(DEBUG                "Debug mode"                            OFF)
set(MAX_SDK_ROOT "C:/Program Files/Autodesk" CACHE PATH "MAX_SDK_ROOT")
set(MAX_EDITOR_ROOT "D:/Program Files/Autodesk" CACHE PATH "MAX_EDITOR_ROOT")

set(MAX_SDK_INCLUDE_PATH "${MAX_SDK_ROOT}/3ds Max 2015 SDK/maxsdk/include" "${MAX_SDK_ROOT}/3ds Max 2015 SDK/maxsdk/include/IGame")
set(MAX_SDK_LIB_PATH "${MAX_SDK_ROOT}/3ds Max 2015 SDK/maxsdk/lib/x64/Release")
set(MAX_SDK_PLUGIN_PATH "${MAX_SDK_ROOT}/3ds Max 2015/plugins")
set(MAX_SDK_EXE_PATH "${MAX_SDK_ROOT}/Autodesk/3ds Max 2015/3dsmax.exe")

# Force out-of-source build
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR
    "This project requires an out of source build. Remove the file 'CMakeCache.txt' found in this directory before continuing, create a separate build directory and run 'cmake [options] <srcs>' from there."
  )
endif()

# TODO: allow other compilers under windows in the future
if(WIN32 AND NOT MSVC)
  message(FATAL_ERROR
    "Under Windows other compiler than Microsoft Visual Studio are not supported."
  )
endif()

# TODO: remove this in the future! it has only been added to make the switch easier for end users
if(PREFIX)
  message(FATAL_ERROR "The parameter PREFIX has been removed. Please re-run CMake and use CMAKE_INSTALL_PREFIX instead to define your installation location!")
endif()

# Some small tweaks for Visual Studio 7 and above.
if(MSVC)
  # Mark 32 bit executables large address aware so they can use > 2GB address space
  if(PLATFORM MATCHES X86)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
  endif()
endif()

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_subdirectory(AwayExtensions-3dsmax)
add_subdirectory(awd-sdk)

