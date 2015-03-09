set(LIBRARY_NAME libawd)

cmake_policy(SET CMP0043 NEW)
file(GLOB INCS cpp-libawd/include/*.h cpp-libawd/include/*.c cpp-libawd/include/*.cpp)
file(GLOB SRCS cpp-libawd/src/*.h cpp-libawd/src/*.c cpp-libawd/src/*.cpp)
file(GLOB ZLIB cpp-libawd/zlib/*.h cpp-libawd/zlib/*.c cpp-libawd/zlib/*.cpp)
file(GLOB LZMA cpp-libawd/lzma/*.h cpp-libawd/lzma/*.c cpp-libawd/lzma/*.cpp)
set(LIBRARY_SRCS )

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(${LIBRARY_NAME} STATIC
  ${LIBRARY_SRCS}
)