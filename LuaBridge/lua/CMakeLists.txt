project(Lua)

# 只处理 win32 平台  
if(WIN32)
	message(STATUS "Lua Project")
	set(SRCS
		./lapi.c
		./lapi.h
		./lauxlib.c
		./lauxlib.h
		./lbaselib.c
		./lbitlib.c
		./lcode.c
		./lcode.h
		./lcorolib.c
		./lctype.c
		./lctype.h
		./ldblib.c
		./ldebug.c
		./ldebug.h
		./ldo.c
		./ldo.h
		./ldump.c
		./lfunc.c
		./lfunc.h
		./lgc.c
		./lgc.h
		./linit.c
		./liolib.c
		./llex.c
		./llex.h
		./llimits.h
		./lmathlib.c
		./lmem.c
		./lmem.h
		./loadlib.c
		./lobject.c
		./lobject.h
		./lopcodes.c
		./lopcodes.h
		./loslib.c
		./lparser.c
		./lparser.h
		./lprefix.h
		./lstate.c
		./lstate.h
		./lstring.c
		./lstring.h
		./lstrlib.c
		./ltable.c
		./ltable.h
		./ltablib.c
		./ltm.c
		./ltm.h
		./lua.c
		./lua.h
		./lua.hpp
		#./luac.c
		./luaconf.h
		./lualib.h
		./lundump.c
		./lundump.h
		./lutf8lib.c
		./lvm.c
		./lvm.h
		./lzio.c
		./lzio.h
	)

	source_group("Src" FILES ${SRCS})
    include_directories(.)
	
	# Lua 定义成 Dll，具体看 luaconf.h， LUA_CORE 已经在  Lua 源代码中有定义了，因此使用 LUA_LIB 
	ADD_DEFINITIONS(-DLUA_BUILD_AS_DLL -DLUA_CORE)
    ADD_LIBRARY(Lua SHARED ${SRCS})
	set_target_properties(Lua PROPERTIES DEBUG_POSTFIX _d)
	
	
	install(FILES 
		${Lua_BINARY_DIR}/Debug/Lua_d.dll
		DESTINATION "${Lua_BINARY_DIR}/../../QtGameEditor/Debug" CONFIGURATIONS Debug
	)
	install(FILES 
		${Lua_BINARY_DIR}/Release/Lua.dll
		DESTINATION "${Lua_BINARY_DIR}/../../QtGameEditor/Release" CONFIGURATIONS Release None ""
	)
	install(FILES 
		${Lua_BINARY_DIR}/RelWithDebInfo/Lua.dll
		DESTINATION "${Lua_BINARY_DIR}/../../QtGameEditor/RelWithDebInfo" CONFIGURATIONS RelWithDebInfo
	)
	install(FILES 
		${Lua_BINARY_DIR}/MinSizeRel/Lua.dll
		DESTINATION "${Lua_BINARY_DIR}/../../QtGameEditor/MinSizeRel" CONFIGURATIONS MinSizeRel
	)
endif(WIN32)