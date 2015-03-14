set(LIBRARY_NAME Easy)

cmake_policy(SET CMP0043 NEW)

file(GLOB_RECURSE LIBRARY_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.rc)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${MAX_SDK_INCLUDE_PATH}
	"${MAX_SDK_ROOT}/3ds Max 2015 SDK/maxsdk/samples/modifiers/morpher"
	"${MAX_SDK_ROOT}/3ds Max 2015 SDK/maxsdk/include/CS"
	${CMAKE_SOURCE_DIR}/tinyxml2
	${CMAKE_SOURCE_DIR}/nvidia-texture-tools/src
	${CMAKE_SOURCE_DIR}/nvidia-texture-tools/extern/poshlib
	${CMAKE_SOURCE_DIR}/nvidia-texture-tools/build/src
	${CMAKE_SOURCE_DIR}/nvidia-texture-tools/build/include
)
link_directories(${MAX_SDK_LIB_PATH} ${CMAKE_SOURCE_DIR}/nvidia-texture-tools/build/lib/static "${MAX_SDK_ROOT}/3ds Max 2015 SDK/maxsdk/samples/modifiers/morpher/Lib/x64/Release")

add_library(${LIBRARY_NAME} SHARED
	${LIBRARY_SRCS}
)

add_dependencies(${LIBRARY_NAME} tinyxml2)

target_link_libraries(${LIBRARY_NAME}
	core
	geom
	gfx
	bmm
	mesh
	maxutil
	maxscrpt
	paramblk2
	IGame
	biped
	assetmanagement
		
	Morpher

	nvcore
	nvimage
	nvmath
	nvthread
	nvtt
	squish
	bc6h
	bc7
	
	tinyxml2
)

set_target_properties(${LIBRARY_NAME} PROPERTIES OUTPUT_NAME "easy_2015_64" SUFFIX ".dle")

install(FILES 
		${CMAKE_CURRENT_BINARY_DIR}/Debug/easy_2015_64.dle
		DESTINATION "${MAX_SDK_PLUGIN_PATH}" CONFIGURATIONS Debug
	)
	install(FILES 
		${CMAKE_CURRENT_BINARY_DIR}/Release/easy_2015_64.dle
		DESTINATION "${MAX_SDK_PLUGIN_PATH}" CONFIGURATIONS Release None ""
	)