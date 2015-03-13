set(LIBRARY_NAME 3dMaxExport)

project(${LIBRARY_NAME})

cmake_policy(SET CMP0043 NEW)
cmake_policy(SET CMP0046 NEW)

file(GLOB SRCS Src/*.h Src/*.cpp)
set(LIBRARY_SRCS ${SRCS})

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/Src
  ${CMAKE_SOURCE_DIR}/Extern/assimp-3.1.1/include
)

if(WIN32)
	add_executable(${LIBRARY_NAME} WIN32 ${LIBRARY_SRCS})
endif()

set_target_properties(${LIBRARY_NAME} PROPERTIES DEBUG_POSTFIX _d LINK_FLAGS "/SUBSYSTEM:\"CONSOLE\"")

target_link_libraries(${LIBRARY_NAME}  assimp)
add_dependencies(${LIBRARY_NAME} assimp)