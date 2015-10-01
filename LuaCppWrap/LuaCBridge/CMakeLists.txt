set (PROJECT_NAME LuaCBridge)
project(${PROJECT_NAME})

message(STATUS "${PROJECT_NAME} Project")
set(SRC_FILES
	./LuaCommon.h
	./LuaCBase.h
	./LuaCBase.cpp
	./LuaCBridge.h
	./LuaCBridge.cpp
	./LuaCFunction.h
	./LuaCFunction.cpp
	./LuaCMember.h
	./LuaCMember.cpp
	./LuaCObject.h
	./LuaCObject.cpp
	./LuaCObjectTranslator.h
	./LuaCObjectTranslator.cpp
	./LuaCScriptMgr.h
	./LuaCScriptMgr.cpp
	./LuaCTable.h
	./LuaCTable.cpp
	./LuaCVM.h
	./LuaCVM.cpp
	./LuaScriptException.h
	./LuaScriptException.cpp
	./LuaCustomLoader.h
	./LuaCustomLoader.cpp
)

source_group("Src" FILES ${SRC_FILES})
include_directories(. ../lua)

ADD_LIBRARY(${PROJECT_NAME} STATIC ${SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Lua)
add_dependencies(${PROJECT_NAME} Lua)