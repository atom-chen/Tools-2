set(LIBRARY_NAME 3dMaxExport)

project(${LIBRARY_NAME})

cmake_policy(SET CMP0043 NEW)
file(GLOB SRCS Src/*.h Src/*.cpp)
set(LIBRARY_SRCS ${SRCS})

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/Src
)

if(WIN32)
	add_executable(${LIBRARY_NAME} WIN32 ${LIBRARY_SRCS})
endif()

#target_link_libraries(${LIBRARY_NAME}  Assimp)
#add_dependencies(${LIBRARY_NAME} Assimp)