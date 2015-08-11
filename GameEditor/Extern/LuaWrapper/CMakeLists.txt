project(LuaWrapper)

# 只处理 win32 平台  
if(WIN32)
	message(STATUS "LuaWrapper Project")
	set(SRCS
		./lua/lua.cpp
		./lua/lua.h
		./lua/luadebug.cpp
		./lua/luadebug.h
		./lua/luadump.cpp
		./lua/luadump.h
		./lua/luaexception.h
		./lua/luaobject.cpp
		./lua/luaobject.h
		./lua/luareference.cpp
		./lua/luareference.h
		./lua/luathread.cpp
		./lua/luathread.h
		./lua/luatypedefs.h
		./lua/luatypes.cpp
		./lua/luatypes.h
		./lua/utils/callhelper.cpp
		./lua/utils/callhelper.h
		./lua/utils/mangler.cpp
		./lua/utils/mangler.h
		./lua/utils/overloadtable.cpp
		./lua/utils/overloadtable.h
		./lua/utils/safecall.cpp
		./lua/utils/safecall.h
		./lua/utils/tuplecall.h
		./lua/utils/tupleforeach.h
		./lua/utils/tuplestack.h
		./lua/table/luactable.cpp
		./lua/table/luactable.h
		./lua/table/luatable.cpp
		./lua/table/luatable.h
		./lua/function/luacfunction.cpp
		./lua/function/luacfunction.h
		./lua/function/luacmethod.cpp
		./lua/function/luacmethod.h
		./lua/function/luafunction.cpp
		./lua/function/luafunction.h
		./lua/function/luamethod.cpp
		./lua/function/luamethod.h
	)

	source_group("Src" FILES ${SRCS})
    include_directories(./lua ./lua/utils ./lua/table ./lua/function ../lua/src)
	
    ADD_LIBRARY(LuaWrapper SHARED ${SRCS})
	set_target_properties(LuaWrapper PROPERTIES DEBUG_POSTFIX _d)
	
	
	install(FILES 
		${LuaWrapper_BINARY_DIR}/Debug/LuaWrapper_d.dll
		DESTINATION "${LuaWrapper_BINARY_DIR}/../../QtGameEditor/Debug" CONFIGURATIONS Debug
	)
	install(FILES 
		${LuaWrapper_BINARY_DIR}/Release/LuaWrapper.dll
		DESTINATION "${LuaWrapper_BINARY_DIR}/../../QtGameEditor/Release" CONFIGURATIONS Release None ""
	)
	install(FILES 
		${LuaWrapper_BINARY_DIR}/RelWithDebInfo/LuaWrapper.dll
		DESTINATION "${LuaWrapper_BINARY_DIR}/../../QtGameEditor/RelWithDebInfo" CONFIGURATIONS RelWithDebInfo
	)
	install(FILES 
		${LuaWrapper_BINARY_DIR}/MinSizeRel/LuaWrapper.dll
		DESTINATION "${LuaWrapper_BINARY_DIR}/../../QtGameEditor/MinSizeRel" CONFIGURATIONS MinSizeRel
	)
endif(WIN32)