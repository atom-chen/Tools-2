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
	./Src/LuaCBridge/LuaCBase.h
	./Src/LuaCBridge/LuaCBase.cpp
	./Src/LuaCBridge/LuaCScriptMgr.h
	./Src/LuaCBridge/LuaCScriptMgr.cpp
	./Src/LuaCBridge/LuaCBridge.h
	./Src/LuaCBridge/LuaCBridge.cpp
	./Src/LuaCBridge/LuaCObject.h
	./Src/LuaCBridge/LuaCObject.cpp
	./Src/LuaCBridge/LuaCTable.h
	./Src/LuaCBridge/LuaCTable.cpp
	./Src/LuaCBridge/LuaCVM.h
	./Src/LuaCBridge/LuaCVM.cpp
	./Src/LuaCBridge/LuaCFunction.h
	./Src/LuaCBridge/LuaCFunction.cpp
	./Src/LuaCBridge/LuaCObjectTranslator.h
	./Src/LuaCBridge/LuaCObjectTranslator.cpp
	./Src/LuaCBridge/LuaCMember.h
	./Src/LuaCBridge/LuaCMember.cpp
	./Src/LuaCBridge/LuaScriptException.h
	./Src/LuaCBridge/LuaScriptException.cpp
	./Src/LuaCBridge/LuaCommon.h
)

set(LUA_C_TEST_FILES
	./Src/LuaCWrap/LuaCTest.h
	./Src/LuaCWrap/LuaCTest.cpp
	./Src/LuaCWrap/LuaCTestWrap.h
	./Src/LuaCWrap/LuaCTestWrap.cpp
)

set(OGRESYS_FILES
	./Src/OgreSys/OgreSys.h
	./Src/OgreSys/OgreSys.cpp	
)

source_group("Base" FILES ${SRCS_FILES})
source_group("TreeData" FILES ${TREE_DATA_FILES})
source_group("ListData" FILES ${LIST_DATA_FILES})
source_group("TabData" FILES ${TAB_DATA_FILES})
source_group("NodeData" FILES ${NODE_DATA_FILES})
source_group("SkillAction" FILES ${SKILLACTION_DATA_FILES})
source_group("LuaCBridge" FILES ${LUA_C_BRIDGE_FILES})
source_group("LuaCWrap" FILES ${LUA_C_TEST_FILES})
source_group("OgreSys" FILES ${OGRESYS_FILES})

set(BOOST_ROOT $ENV{BOOST_ROOT})
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost
			 1.57.0
			 COMPONENTS thread filesystem
			 REQUIRED)

# Create debug libraries with _d postfix
set(CMAKE_DEBUG_POSTFIX "_d")

include_directories(./Src ./Src/TreeData ./Src/ListData ./Src/NodeData ./Src/SkillAction ./Src/LuaCBridge ./Src/LuaCWrap ../Extern/tinyxml ../Extern/lua/src ./Src/OgreSys)
include_directories(../Extern/ogre/build/sdk/include/OGRE ../Extern/ogre/build/sdk/include/OGRE/Hlms/Unlit ../Extern/ogre/build/sdk/include/OGRE/Hlms/Pbs ../Extern/ogre/build/sdk/include/OGRE/Compositor ../Extern/ogre/build/sdk/include/OIS ${Boost_INCLUDE_DIRS})
link_directories(../Extern/ogre/build/sdk/lib ${Boost_LIBRARY_DIRS})

ADD_DEFINITIONS(-DGAMEEDITOR_DLL -DGAMEEDITOR_DLL_EXPORT)

#set(ALL_SRCS ${SRCS_FILES} ${MOC_SRCS} ${UI_SRCS} ${QRC_SRCS} ${RC_FILES})
set(ALL_SRCS ${SRCS_FILES} ${TREE_DATA_FILES} ${LIST_DATA_FILES} ${TAB_DATA_FILES} ${NODE_DATA_FILES} ${SKILLACTION_DATA_FILES} ${LUA_C_BRIDGE_FILES} ${LUA_C_TEST_FILES} ${OGRESYS_FILES})

ADD_LIBRARY(GameEditor SHARED ${ALL_SRCS})

set_target_properties(GameEditor PROPERTIES DEBUG_POSTFIX _d)

TARGET_LINK_LIBRARIES(GameEditor tinyxml Lua OgreMain_d OgreHlmsUnlit_d OgreHlmsPbs_d OIS_d)

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