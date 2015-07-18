project(Lua)

# 只处理 win32 平台  
if(WIN32)
	message(STATUS "Lua Project")
	set(SRCS
		./src/lapi.c
		./src/lapi.h
		./src/lauxlib.c
		./src/lauxlib.h
		./src/lbaselib.c
		./src/lbitlib.c
		./src/lcode.c
		./src/lcode.h
		./src/lcorolib.c
		./src/lctype.c
		./src/lctype.h
		./src/ldblib.c
		./src/ldebug.c
		./src/ldebug.h
		./src/ldo.c
		./src/ldo.h
		./src/ldump.c
		./src/lfunc.c
		./src/lfunc.h
		./src/lgc.c
		./src/lgc.h
		./src/linit.c
		./src/liolib.c
		./src/llex.c
		./src/llex.h
		./src/llimits.h
		./src/lmathlib.c
		./src/lmem.c
		./src/lmem.h
		./src/loadlib.c
		./src/lobject.c
		./src/lobject.h
		./src/lopcodes.c
		./src/lopcodes.h
		./src/loslib.c
		./src/lparser.c
		./src/lparser.h
		./src/lprefix.h
		./src/lstate.c
		./src/lstate.h
		./src/lstring.c
		./src/lstring.h
		./src/lstrlib.c
		./src/ltable.c
		./src/ltable.h
		./src/ltablib.c
		./src/ltm.c
		./src/ltm.h
		./src/lua.c
		./src/lua.h
		./src/lua.hpp
		#./src/luac.c
		./src/luaconf.h
		./src/lualib.h
		./src/lundump.c
		./src/lundump.h
		./src/lutf8lib.c
		./src/lvm.c
		./src/lvm.h
		./src/lzio.c
		./src/lzio.h
	)

	source_group("Src" FILES ${SRCS})
    include_directories(.)
	
	# Lua 定义成 Dll，具体看 luaconf.h
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