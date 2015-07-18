project(GameEditor)

cmake_minimum_required(VERSION 2.8.10)
#set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
#cmake_policy(SET CMP0003 NEW)

set (CMAKE_PREFIX_PATH "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64" ${CMAKE_PREFIX_PATH})

# CMake policy introduced in relation to Qt 5.1
if("${CMAKE_VERSION}" VERSION_GREATER 2.8.11)   
	cmake_policy(SET CMP0020 OLD)
endif()

set(SRCS_FILES
	./Src/Platform.h
	./Src/Prerequisites.h
	./Src/GameEditor.h
	./Src/GlobalDefine.h
	./Src/Singleton.h
	./Src/Aaa.h
	./Src/Aaa.cpp
	./Src/GameEditorSys.h
	./Src/GameEditorSys.cpp
	./Src/PushWarn.h
	./Src/PopWarn.h
)

set(TREE_DATA_FILES
	./Src/TreeData/MyBasicTreeWidgetItemLogicData.h
	./Src/TreeData/MyBasicTreeWidgetItemLogicData.cpp
)

set(LIST_DATA_FILES
	./Src/ListData/MyBasicListWidgetItemLogicData.h
	./Src/ListData/MyBasicListWidgetItemLogicData.cpp
)

set(TAB_DATA_FILES
	./Src/TabData/TabSubWidgetLogicData.h
	./Src/TabData/TabSubWidgetLogicData.cpp
)

set(NODE_DATA_FILES
	./Src/NodeData/NodeDataBase.h
	./Src/NodeData/NodeDataBase.cpp
	./Src/NodeData/NodeDataMgr.h
	./Src/NodeData/NodeDataMgr.cpp
	./Src/NodeData/TestNodeData.h
	./Src/NodeData/TestNodeData.cpp
)

set(SKILLACTION_DATA_FILES
	./Src/SkillAction/SkillActionNodeConfig.h
	./Src/SkillAction/SkillActionNodeConfig.cpp
)

set(LUA_C_BRIDGE_FILES
	./Src/LuaCBridge/LuaCScriptMgr.h
	./Src/LuaCBridge/LuaCScriptMgr.cpp
	./Src/LuaCBridge/LuaCBridge.h
	./Src/LuaCBridge/LuaCBridge.cpp
	./Src/LuaCBridge/LuaCObject.h
	./Src/LuaCBridge/LuaCObject.cpp
	./Src/LuaCBridge/LuaCTable.h
	./Src/LuaCBridge/LuaCTable.cpp
)

source_group("Base" FILES ${SRCS_FILES})
source_group("TreeData" FILES ${TREE_DATA_FILES})
source_group("ListData" FILES ${LIST_DATA_FILES})
source_group("TabData" FILES ${TAB_DATA_FILES})
source_group("NodeData" FILES ${NODE_DATA_FILES})
source_group("SkillAction" FILES ${SKILLACTION_DATA_FILES})
source_group("LuaCBridge" FILES ${LUA_C_BRIDGE_FILES})

include_directories(./Src ./Src/TreeData ./Src/ListData ./Src/NodeData ./Src/SkillAction ./Src/LuaCBridge ../Extern/tinyxml ../Extern/lua/src)

ADD_DEFINITIONS(-DGAMEEDITOR_DLL -DGAMEEDITOR_DLL_EXPORT)

#set(ALL_SRCS ${SRCS_FILES} ${MOC_SRCS} ${UI_SRCS} ${QRC_SRCS} ${RC_FILES})
set(ALL_SRCS ${SRCS_FILES} ${TREE_DATA_FILES} ${LIST_DATA_FILES} ${TAB_DATA_FILES} ${NODE_DATA_FILES} ${SKILLACTION_DATA_FILES} ${LUA_C_BRIDGE_FILES})

ADD_LIBRARY(GameEditor SHARED ${ALL_SRCS})

set_target_properties(GameEditor PROPERTIES DEBUG_POSTFIX _d)

TARGET_LINK_LIBRARIES(GameEditor tinyxml Lua)

add_dependencies(GameEditor tinyxml Lua)

#set(INST_FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}${DEBUG_POSTFIX})
#set(INST_FILES ${LIBRARY_OUTPUT_DIR}/${PROJECT_NAME}${DEBUG_POSTFIX}.dll)
#set(INST_FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}${DEBUG_POSTFIX}.dll)

#install(FILES 
#	${INST_FILES} DESTINATION "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}"
#)

install(FILES 
	${GameEditor_BINARY_DIR}/Debug/GameEditor_d.dll
	DESTINATION "${GameEditor_BINARY_DIR}/../QtGameEditor/Debug" CONFIGURATIONS Debug
)
install(FILES 
	${GameEditor_BINARY_DIR}/Release/GameEditor.dll
	DESTINATION "${GameEditor_BINARY_DIR}/../QtGameEditor/Release" CONFIGURATIONS Release None ""
)
install(FILES 
	${GameEditor_BINARY_DIR}/RelWithDebInfo/GameEditor.dll
	DESTINATION "${GameEditor_BINARY_DIR}/../QtGameEditor/RelWithDebInfo" CONFIGURATIONS RelWithDebInfo
)
install(FILES 
	${GameEditor_BINARY_DIR}/MinSizeRel/GameEditor.dll
	DESTINATION "${GameEditor_BINARY_DIR}/../QtGameEditor/MinSizeRel" CONFIGURATIONS MinSizeRel
)