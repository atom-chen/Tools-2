set (PROJECT_NAME LuaBridge)
project(${PROJECT_NAME})

message(STATUS "${PROJECT_NAME} Project")
set(SRC_FILES
	./LuaBridge.h
	./RefCountedObject.h
	./RefCountedPtr.h
	./detail/CFunctions.h
	./detail/ClassInfo.h
	./detail/Constructor.h
	./detail/dump.h
	./detail/FuncTraits.h
	./detail/Iterator.h
	./detail/LuaException.h
	./detail/LuaHelpers.h
	./detail/LuaRef.h
	./detail/Namespace.h
	./detail/Stack.h
	./detail/TypeList.h
	./detail/TypeTraits.h
	./detail/Userdata.h
)

source_group("Inc" FILES ${SRC_FILES})
include_directories(.)

ADD_LIBRARY(${PROJECT_NAME} STATIC ${SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)