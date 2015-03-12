set(LIBRARY_NAME_maxawdexporter maxawdexporter)

cmake_policy(SET CMP0043 NEW)

file(GLOB_RECURSE GLM_INCS ${CMAKE_SOURCE_DIR}/glm-0.9.6.3/glm/*.hpp ${CMAKE_SOURCE_DIR}/glm-0.9.6.3/glm/*.inl)

set(LIBRARY_SRCS_maxawdexporter
	${CMAKE_CURRENT_SOURCE_DIR}/src/3dsmaxsdk_preinclude.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/cache.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporteropts.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/resource.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/resourceexporter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/utils.h
	
	${CMAKE_CURRENT_SOURCE_DIR}/src/cache.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/DllEntryexporter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporter_anim.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporter_camera.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporter_geometry.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporter_helper.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporter_materials.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporter_methods.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporter_scenegraph.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporter_shadows.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporter_textures.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdexporteropts.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/maxawd_exporter.rc
	${CMAKE_CURRENT_SOURCE_DIR}/maxawd.def
	
	${GLM_INCS}
)

source_group("GLM" FILES ${GLM_INCS})

include_directories(
	${CMAKE_SOURCE_DIR}/awd-sdk/cpp-libawd/include
	${CMAKE_SOURCE_DIR}/awd-sdk/cpp-libawd/lib/zlib
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${MAX_SDK_INCLUDE_PATH}
	${CMAKE_SOURCE_DIR}/glm-0.9.6.3
)
link_directories(${MAX_SDK_LIB_PATH})

#SET(LIBRARY_OUTPUT_PATH ${MAX_SDK_PLUGIN_PATH})

add_library(${LIBRARY_NAME_maxawdexporter} SHARED
	${LIBRARY_SRCS_maxawdexporter}
)

add_dependencies(${LIBRARY_NAME_maxawdexporter} libawd)
target_link_libraries(${LIBRARY_NAME_maxawdexporter}
	assetmanagement
	core
	geom
	gfx
	mesh
	maxutil
	maxscrpt
	paramblk2
	bmm
	iGame
	libawd
)

set_target_properties(${LIBRARY_NAME_maxawdexporter} PROPERTIES OUTPUT_NAME "maxawdexporter_2015_64" SUFFIX ".dle")
EXEC_PROGRAM(${MAX_SDK_EXE_PATH} ARGS ${MAX_SDK_PLUGIN_PATH}/maxawdexporter_2015_64.dle)

install(FILES 
		${CMAKE_CURRENT_BINARY_DIR}/Debug/maxawdexporter_2015_64.dle
		DESTINATION "${MAX_SDK_PLUGIN_PATH}" CONFIGURATIONS Debug
	)
	install(FILES 
		${CMAKE_CURRENT_BINARY_DIR}/Release/maxawdexporter_2015_64.dle
		DESTINATION "${MAX_SDK_PLUGIN_PATH}" CONFIGURATIONS Release None ""
	)

##############################################################
#set(LIBRARY_NAME_maxawdimporter maxawdimporter)

#cmake_policy(SET CMP0043 NEW)

#set(LIBRARY_SRCS_maxawdimporter
#	${CMAKE_CURRENT_SOURCE_DIR}/src/3dsmaxsdk_preinclude.h
#	${CMAKE_CURRENT_SOURCE_DIR}/src/cacheimporter.h
#	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdimporter.h
#	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdimporterblocks.h
#	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdimporteropts.h
#	${CMAKE_CURRENT_SOURCE_DIR}/src/resourceimporter.h
#	${CMAKE_CURRENT_SOURCE_DIR}/src/utils.h
#	
#	${CMAKE_CURRENT_SOURCE_DIR}/src/cacheimporter.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/src/DllEntryimporter.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdimporter.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdimporterblocks.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/src/maxawdimporteropts.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
#	
#	${CMAKE_CURRENT_SOURCE_DIR}/maxawd_importer.rc
#	${CMAKE_CURRENT_SOURCE_DIR}/maxawd.def
#)

#add_library(${LIBRARY_NAME_maxawdimporter} SHARED
#	${LIBRARY_SRCS_maxawdimporter}
#)

#add_dependencies(${LIBRARY_NAME_maxawdimporter} libawd)
#target_link_libraries(${LIBRARY_NAME_maxawdimporter}
#	assetmanagement
#	core
#	geom
#	gfx
#	mesh
#	maxutil
#	maxscrpt
#	paramblk2
#	bmm
#	iGame
#	libawd
#)

#set_target_properties(${LIBRARY_NAME_maxawdimporter} PROPERTIES OUTPUT_NAME "maxawdimporter_2015_64" SUFFIX ".dle")

#set_target_properties(${LIBRARY_NAME_maxawdimporter} PROPERTIES
#     IMPORTED_LOCATION_RELEASE ${CMAKE_CURRRENT_BINARY_DIR}/Debug/maxawdimporter.dle
#     IMPORTED_LOCATION_DEBUG   ${CMAKE_CURRRENT_BINARY_DIR}/Release/maxawdimporter.dle)