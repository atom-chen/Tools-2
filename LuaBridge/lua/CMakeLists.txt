project(Lua)

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

# lua 不适合使用 VS 编译 DLL ，因为 VS 如果要编译 Lua DLL ，需要一个 def 文件才行，否则会有编译警告。VS 工程中如果定义 LUA_LIB 或者 LUA_CORE ，就会有警告，如果不定义，#define LUA_API __declspec(dllimport) ，因此都有问题
# Lua 定义成 Dll，具体看 luaconf.h， LUA_CORE 已经在  Lua 源代码中有定义了，因此使用 LUA_LIB 
#ADD_DEFINITIONS(-DLUA_BUILD_AS_DLL -DLUA_CORE)
#ADD_DEFINITIONS(-DLUA_BUILD_AS_DLL -DLUA_LIB)
#ADD_LIBRARY(Lua SHARED ${SRCS})
ADD_LIBRARY(Lua STATIC ${SRCS})
set_target_properties(Lua PROPERTIES DEBUG_POSTFIX _d)