project(LzmaLib)

cmake_minimum_required(VERSION 2.8.10)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)

set (CMAKE_PREFIX_PATH "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64" ${CMAKE_PREFIX_PATH})

if("${CMAKE_VERSION}" VERSION_GREATER 2.8.11)   
	cmake_policy(SET CMP0020 OLD)
endif()

SET(SRCS_FILES
	./Alloc.c
	./Alloc.h
	./LzFind.c
	./LzFind.h
	./LzFindMt.c
	./LzFindMt.h
	./LzHash.h
	./LzmaDec.c
	./LzmaDec.h
	./LzmaEnc.c
	./LzmaEnc.h
	./LzmaLib.c
	./LzmaLib.h
	./Threads.c
	./Threads.h
	./Types.h
	./Util/LzmaLib/resource.rc
)

SET(DEF_FILES
	./Util/LzmaLib/LzmaLibExports.c
	./Util/LzmaLib/LzmaLib.def
)

source_group("Spec" FILES ${DEF_FILES})
source_group("" FILES ${SRCS_FILES})

include_directories(.)

set(ALL_SRCS ${DEF_FILES} ${SRCS_FILES})

ADD_LIBRARY(LzmaLib SHARED ${ALL_SRCS})

set_target_properties(LzmaLib PROPERTIES DEBUG_POSTFIX _d)