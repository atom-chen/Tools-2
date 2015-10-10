#include "LuaCVM.h"
#include "LuaCObjectTranslator.h"
#include "LuaCObject.h"
#include "LuaCTable.h"
#include "LuaCFunction.h"
#include "LuaCMember.h"
#include "LuaCommon.h"
#include "LuaScriptException.h"
#include <sstream>
#include <string>
#include <LuaCUtil.h>

LuaCVM::LuaCVM()
{
	translator = new LuaCObjectTranslator;
	openLua();


	luaIndex = 
		"        \
		local rawget = rawget \
		local rawset = rawset \
		local getmetatable = getmetatable \
		local type = type \
		local function index(obj, name) \
		local o = obj \
		local meta = getmetatable(o) \
		local parent = meta \
		local v = nil \
					\
		while meta~= nil do \
			v = rawget(meta, name) \
							\
			if v~= nil then \
				if parent ~= meta then rawset(parent, name, v) end \
									\
					local t = type(v) \
											\
					if t == 'function' then \
						return v \
					else \
					local func = v[1] \
											\
					if func ~= nil then \
						return func(obj) \
						end \
						end \
						break \
						end \
													\
						meta = getmetatable(meta) \
						end \
													\
						error('unknown member name '..name, 2) \
						return nil \
						end \
						return index";
	
	
	luaNewIndex =
		" \
		local rawget = rawget \
		local getmetatable = getmetatable \
		local rawset = rawset \
		local function newindex(obj, name, val) \
		local meta = getmetatable(obj) \
		local parent = meta \
		local v = nil \
					\
		while meta~= nil do \
			v = rawget(meta, name) \
							\
			if v~= nil then \
				if parent ~= meta then rawset(parent, name, v) end \
					local func = v[2] \
					if func ~= nil then \
						return func(obj, nil, val) \
						end \
						break \
						end \
													\
						meta = getmetatable(meta) \
						end \
													\
						error('field or property '..name..' does not exist', 2) \
						return nil \
						end \
						return newindex";
	
	luaTableCall =
		" \
		local rawget = rawget \
		local getmetatable = getmetatable \
					\
		local function call(obj, ...) \
		local meta = getmetatable(obj) \
		local fun = rawget(meta, 'New') \
					\
		if fun ~= nil then \
			return fun(...) \
		else \
		error('unknow function __call', 2) \
		end \
		end \
					\
		return call \
		";
	
	luaEnumIndex =
		" \
		local rawget = rawget \
		local getmetatable = getmetatable \
					\
		local function indexEnum(obj, name) \
		local v = rawget(obj, name) \
					\
		if v ~= nil then \
			return v \
			end \
							\
			local meta = getmetatable(obj) \
			local func = rawget(meta, name) \
							\
			if func ~= nil then \
				v = func() \
				rawset(obj, name, v) \
				return v \
			else \
			error('field '..name..' does not exist', 2) \
			end \
			end \
							\
			return indexEnum \
			";
	
	lua_pushstring(L, "ToLua_Index");
	luaL_dostring(L, luaIndex.c_str());
	lua_rawset(L, LUA_REGISTRYINDEX);
	
	lua_pushstring(L, "ToLua_NewIndex");
	luaL_dostring(L, luaNewIndex.c_str());
	lua_rawset(L, LUA_REGISTRYINDEX);
	
	lua_pushstring(L, "ToLua_TableCall");
	luaL_dostring(L, luaTableCall.c_str());
	lua_rawset(L, LUA_REGISTRYINDEX);
	
	lua_pushstring(L, "ToLua_EnumIndex");
	luaL_dostring(L, luaEnumIndex.c_str());
	lua_rawset(L, LUA_REGISTRYINDEX);
	
	//Bind();
	
#if MULTI_STATE
	mgrList.Add(this);
	LuaDLL.lua_pushnumber(lua.L, mgrPos);
	LuaDLL.lua_setglobal(lua.L, "_LuaScriptMgr");
	
	++mgrPos;
#else
	lua_pushnumber(L, 0);
	lua_setglobal(L, "_LuaScriptMgr");
#endif
	//CmdTable.RegisterCommand("ToLua", ToLua.Generate);
	//CmdTable.RegisterCommand("LuaGC", LuaGC);
	//CmdTable.RegisterCommand("memory", LuaMem);
	//CmdTable.RegisterCommand("GM", SendGMmsg); 
	
	setLuaFilePath("D:/file/opensource/unity-game-git/unitygame/Tools/GameEditor/LuaScript");
	luaL_dofile(L, "TestLua.lua");
}

LuaCVM::~LuaCVM()
{

}

void LuaCVM::openLua()
{
	/* initialize Lua */
	// L = lua_open();			// Lua5.1
	L = luaL_newstate();		// Lua5.3
	/* load Lua libraries */
	luaL_openlibs(L);
}

void LuaCVM::closeLua()
{
	lua_close(L);
}

void LuaCVM::doString(std::string value)
{
	int ret = luaL_dostring(L, value.c_str());
	if (LUA_OK == ret)	// 执行成功
	{

	}
	else if (LUA_ERRRUN == ret)	// a runtime error. 
	{

	}
	else if (LUA_ERRMEM == ret)	// memory allocation error. For such errors, Lua does not call the error handler function. 
	{

	}
	else if (LUA_ERRERR == ret)	// error while running the error handler function. 
	{

	}
}

void LuaCVM::doFile(std::string path)
{
	luaL_dofile(L, path.c_str());
}

LuaCObject* LuaCVM::getLuaObject(std::string fullPath)
{
	LuaCObject* returnValue = nullptr;
	int oldTop = lua_gettop(L);
	std::vector<std::string> path;
	std::string delim = ".";
	LuaCUtil::split(fullPath, delim, &path);

	lua_getglobal(L, path[0].c_str());
	returnValue = translator->getObject(-1);
	if (path.size() > 1)
	{
		std::vector<std::string> remainingPath;
		remainingPath.assign(path.begin() + 1, path.end());
		returnValue = getObject(remainingPath);
	}
	lua_settop(L, oldTop);
	return returnValue;
}

void LuaCVM::setLuaObject(std::string fullPath, LuaCObject* value)
{
	int oldTop = lua_gettop(L);
	std::vector<std::string> path;
	std::string delim = ".";
	LuaCUtil::split(fullPath, delim, &path);

	if (path.size() == 1)
	{
		translator->push(value);
		lua_setglobal(L, fullPath.c_str());
	}
	else
	{
		lua_getglobal(L, path[0].c_str());		// lua5.3 lua_getglobal
		//lua_rawglobal(L, path[0]);			// lua5.1 lua_rawglobal
		int type = lua_type(L, -1);

		if (type == LUA_TNIL)
		{
			// 输出日志
			lua_settop(L, oldTop);
			return;
		}

		std::vector<std::string> remainingPath;;
		remainingPath.assign(path.begin() + 1, path.end());
		setObject(remainingPath, value);
	}

	lua_settop(L, oldTop);
}

LuaCObject* LuaCVM::getObject(std::vector<std::string>& remainingPath)
{
	LuaCObject* returnValue = nullptr;
	for (int i = 0; i < remainingPath.size(); i++)
	{
		lua_pushstring(L, remainingPath[i].c_str());
		lua_gettable(L, -2);
		returnValue = translator->getObject(-1);
		if (returnValue == nullptr) break;
	}
	return returnValue;
}

void LuaCVM::setObject(std::vector<std::string>& remainingPath, LuaCObject* val)
{
	for (int i = 0; i < remainingPath.size() - 1; i++)
	{
		lua_pushstring(L, remainingPath[i].c_str());
		lua_gettable(L, -2);
	}

	lua_pushstring(L, remainingPath[remainingPath.size() - 1].c_str());

	//可以释放先
	//if (val == null)
	//{
	//    LuaDLL.lua_gettable(L, -2);               
	//    LuaTypes type = LuaDLL.lua_type(L, -1);

	//    if (type == LuaTypes.LUA_TUSERDATA)
	//    {
	//        int udata = LuaDLL.luanet_tonetobject(L, -1);

	//        if (udata != -1)
	//        {
	//            translator.collectObject(udata);
	//        }
	//    }
	//}

	translator->push(val);
	lua_settable(L, -3);
}

void LuaCVM::NewTable(std::string fullPath)
{
	std::vector<std::string> path;
	std::string delim = ".";
	LuaCUtil::split(fullPath, delim, &path);

	int oldTop = lua_gettop(L);
	if (path.size() == 1)
	{
		lua_newtable(L);
		lua_setglobal(L, fullPath.c_str());
	}
	else
	{
		lua_getglobal(L, path[0].c_str());
		for (int i = 1; i < path.size() - 1; i++)
		{
			lua_pushstring(L, path[i].c_str());
			lua_gettable(L, -2);
		}
		lua_pushstring(L, path[path.size() - 1].c_str());
		lua_newtable(L);
		lua_settable(L, -3);
	}
	lua_settop(L, oldTop);
}

LuaCTable* LuaCVM::NewTable()
{
	int oldTop = lua_gettop(L);

	lua_newtable(L);
	LuaCTable* returnVal = (LuaCTable*)translator->getObject(-1);

	lua_settop(L, oldTop);
	return returnVal;
}

LuaCObject* LuaCVM::rawGetObject(int reference, std::string field)
{
	int oldTop = lua_gettop(L);
	lua_getref(L, reference);
	lua_pushstring(L, field.c_str());
	lua_rawget(L, -2);
	LuaCObject* obj = translator->getObject(-1);
	lua_settop(L, oldTop);
	return obj;
}
/*
* Gets a field of the table or userdata corresponding to the provided reference
*/
LuaCObject* LuaCVM::getObject(int reference, std::string field)
{
	int oldTop = lua_gettop(L);
	lua_getref(L, reference);

	std::vector<std::string> path;
	std::string delim = ".";
	LuaCUtil::split(field, delim, &path);

	LuaCObject* returnValue = getObject(path);
	lua_settop(L, oldTop);
	return returnValue;
}
/*
* Gets a numeric field of the table or userdata corresponding the the provided reference
*/
LuaCObject* LuaCVM::getObject(int reference, LuaCObject* field)
{
	int oldTop = lua_gettop(L);
	lua_getref(L, reference);
	translator->push(field);
	lua_gettable(L, -2);
	LuaCObject* returnValue = translator->getObject(-1);
	lua_settop(L, oldTop);
	return returnValue;
}
/*
* Sets a field of the table or userdata corresponding the the provided reference
* to the provided value
*/
void LuaCVM::setObject(int reference, std::string field, LuaCObject* val)
{
	int oldTop = lua_gettop(L);
	lua_getref(L, reference);

	std::vector<std::string> path;
	std::string delim = ".";
	LuaCUtil::split(field, delim, &path);

	setObject(path, val);
	lua_settop(L, oldTop);
}
/*
* Sets a numeric field of the table or userdata corresponding the the provided reference
* to the provided value
*/
void LuaCVM::setObject(int reference, LuaCObject* field, LuaCObject* val)
{
	int oldTop = lua_gettop(L);
	lua_getref(L, reference);
	translator->push(field);
	translator->push(val);
	lua_settable(L, -3);
	lua_settop(L, oldTop);
}

// 注册一个函数
LuaCFunction* LuaCVM::RegisterFunction(std::string fullPath, lua_CFunction function)
{
	// We leave nothing on the stack when we are done
	int oldTop = lua_gettop(L);

	std::vector<std::string> path;
	std::string delim = ".";
	LuaCUtil::split(fullPath, delim, &path);

	// 注册到表中
	if (path.size() > 1)
	{
		int dotIdx = static_cast<int>(fullPath.find_last_of("."));
		std::string tablePath = fullPath.substr(0, dotIdx);
		std::string lastPath = fullPath.substr(dotIdx + 1, fullPath.length() - (dotIdx + 1));
		LuaCTable* pLuaCTable = GetLuaTable(tablePath);
		pLuaCTable->setLuaFunction(lastPath, function);
	}
	else	// 注册到全局表中
	{
		lua_register(L, path[path.size() - 1].c_str(), function);	// 全局注册函数请使用这个
	}
	lua_settop(L, oldTop);

	LuaCFunction* f = GetLuaFunction(fullPath);
	return f;
}

//LuaCFunction LuaCVM::CreateFunction(LuaCObject* target, MethodBase function /*MethodInfo function*/)  //CP: Fix for struct constructor by Alexander Kappner (link: http://luaforge.net/forum/forum.php?thread_id=2859&forum_id=145)
//{
//	// We leave nothing on the stack when we are done
//	int oldTop = LuaDLL.lua_gettop(L);
//
//	LuaMethodWrapper wrapper = new LuaMethodWrapper(translator, target, function.DeclaringType, function);
//	translator.push(L, new LuaCSFunction(wrapper.call));
//
//	object obj = translator.getObject(L, -1);
//	LuaFunction f = (obj is LuaCSFunction ? new LuaFunction((LuaCSFunction)obj, this) : (LuaFunction)obj);
//
//	LuaDLL.lua_settop(L, oldTop);
//
//	return f;
//}









void LuaCVM::PrintLua(std::vector<std::string> param)
{
	if (param.size() != 2)
	{
		//Debugger.Log("PrintLua [ModuleName]");
		return;
	}

	std::vector<LuaCObject*> paramList;
	LuaCObject* pLuaCObject = new LuaCObject;
	pLuaCObject->m_type = LUAC_TSTRING;
	pLuaCObject->m_pChar = param[1].c_str();
	CallLuaFunction("PrintLua", paramList);
}

void LuaCVM::LuaGC(std::vector<std::string> param)
{
	lua_gc(L, LUA_GCCOLLECT, 0);
}

void LuaCVM::LuaMem(std::vector<std::string> param)
{
	std::vector<LuaCObject*> paramList;
	CallLuaFunction("mem_report", paramList);
}

void LuaCVM::setLuaFilePath(std::string path)
{
	std::stringstream strStream;
	strStream << "local m_package_path = package.path" << "\r\n" << "package.path = string.format(\"%s;%s/?.lua\", m_package_path, " << path << ")";
	luaL_dostring(L, strStream.str().c_str());
}

void LuaCVM::setCFilePath(std::string path)
{

}

void LuaCVM::CheckArgsCount(int count)
{
	int c = lua_gettop(L);

	if (c != count)
	{
		std::string str = "no overload for method '{0}' takes '{1}' arguments";
		luaL_error(L, str.c_str());
	}
}

//读取object类型，object为万用类型, 能读取所有从lua传递的参数
LuaCObject* LuaCVM::GetVarObject(int stackPos)
{
	LuaCObject* ret = nullptr;
	int type = lua_type(L, stackPos);

	switch (type)
	{
	case LUA_TNUMBER:
		ret->m_float = lua_tonumber(L, stackPos);
	case LUA_TSTRING:
		ret->m_pChar = lua_tostring(L, stackPos);
	case LUA_TUSERDATA:
	{
		ret->m_pUserData = lua_touserdata(L, stackPos);

		//if (udata != -1)
		//{
		//	object obj = null;
		//	GetTranslator(L).objects.TryGetValue(udata, out obj);
		//	return obj;
		//}
		//else
		//{
		//	return null;
		//}
	}
	case LUA_TBOOLEAN:
		ret->m_bool = lua_toboolean(L, stackPos);
	case LUA_TTABLE:
		ret = GetVarTable(stackPos);
	case LUA_TFUNCTION:
		lua_pushvalue(L, stackPos);
		ret->m_pLuaCFunction = new LuaCFunction(luaL_ref(L, LUA_REGISTRYINDEX), GetTranslator()->interpreter);
	default:
		return nullptr;
	}

	return ret;
}

LuaCObject* LuaCVM::GetVarTable(int stackPos)
{
	LuaCObject* o = nullptr;
	int oldTop = lua_gettop(L);
	lua_pushvalue(L, stackPos);
	lua_pushstring(L, "class");
	lua_gettable(L, -2);

	if (lua_isnil(L, -1))
	{
		lua_settop(L, oldTop);
		lua_pushvalue(L, stackPos);
		o->m_pLuaCTable = new LuaCTable(luaL_ref(L, LUA_REGISTRYINDEX), GetTranslator()->interpreter);
	}
	else
	{
		std::string cls = lua_tostring(L, -1);
		lua_settop(L, oldTop);

		stackPos = stackPos > 0 ? stackPos : stackPos + oldTop + 1;

		/*if (cls == "Vector3")
		{
		o = GetVector3(L, stackPos);
		}
		else if (cls == "Vector2")
		{
		o = GetVector2(L, stackPos);
		}
		else if (cls == "Quaternion")
		{
		o = GetQuaternion(L, stackPos);
		}
		else if (cls == "Color")
		{
		o = GetColor(L, stackPos);
		}
		else if (cls == "Vector4")
		{
		o = GetVector4(L, stackPos);
		}
		else if (cls == "Ray")
		{
		o = GetRay(L, stackPos);
		}
		else if (cls == "Bounds")
		{
		o = GetBounds(L, stackPos);
		}
		else
		{
		lua_pushvalue(L, stackPos);
		o = new LuaTable(LuaDLL.luaL_ref(L, LuaIndexes.LUA_REGISTRYINDEX), GetTranslator(L).interpreter);
		}*/
	}

	//LuaDLL.lua_settop(L, oldTop);
	return o;
}

LuaCObjectTranslator* LuaCVM::GetTranslator()
{
	return translator;
}

//压入一个object变量
void LuaCVM::PushVarObject(LuaCObject* o)
{
	if (o == nullptr)
	{
		lua_pushnil(L);
		return;
	}

	int t = o->GetType();

	if (LUAC_TBOOLEAN == t)
	{
		lua_pushnil(L);
	}
	else if (LUAC_TBOOLEAN == t)
	{
		lua_pushboolean(L, o->m_bool);
	}
	else if (LUAC_TLIGHTUSERDATA == t)
	{
		lua_pushlightuserdata(L, o->m_pLightUserData);
	}
	else if (LUAC_TNUMBER == t)
	{
		lua_pushnumber(L, o->m_float);
	}
	else if (LUAC_TSTRING == t)
	{
		lua_pushstring(L, o->m_pChar);
	}
	else if (LUAC_TTABLE == t)
	{
		lua_rawseti(L, LUA_REGISTRYINDEX, o->m_pLuaCTable->getRef());
	}
	else if (LUAC_TFUNCTION == t)
	{
		lua_rawseti(L, LUA_REGISTRYINDEX, o->m_pLuaCFunction->getRef());
	}
	else if (LUAC_TUSERDATA == t)
	{
		//lua_rawseti(L, o->m_pUserData);
	}
	else if (LUAC_TTHREAD == t)
	{

	}
	else
	{
		lua_pushinteger(L, o->m_int);
	}
	//if (t.IsValueType)
	//{
	//	if (t == typeof(bool))
	//	{
	//		bool b = (bool)o;
	//		lua_pushboolean(L, b);
	//	}
	//	else if (t.IsEnum)
	//	{
	//		Push(L, (System.Enum)o);
	//	}
	//	else if (t.IsPrimitive)
	//	{
	//		double d = Convert.ToDouble(o);
	//		lua_pushnumber(L, d);
	//	}
	//	else if (t == typeof(Vector3))
	//	{
	//		Push(L, (Vector3)o);
	//	}
	//	else if (t == typeof(Vector2))
	//	{
	//		Push(L, (Vector2)o);
	//	}
	//	else if (t == typeof(Vector4))
	//	{
	//		Push(L, (Vector4)o);
	//	}
	//	else if (t == typeof(Quaternion))
	//	{
	//		Push(L, (Quaternion)o);
	//	}
	//	else if (t == typeof(Color))
	//	{
	//		Push(L, (Color)o);
	//	}
	//	else if (t == typeof(RaycastHit))
	//	{
	//		Push(L, (RaycastHit)o);
	//	}
	//	else if (t == typeof(Touch))
	//	{
	//		Push(L, (Touch)o);
	//	}
	//	else if (t == typeof(Ray))
	//	{
	//		Push(L, (Ray)o);
	//	}
	//	else
	//	{
	//		PushValue(L, o);
	//	}
	//}
	//else
	//{
	//	if (t.IsArray)
	//	{
	//		PushArray(L, (System.Array)o);
	//	}
	//	else if (t == typeof(LuaCSFunction))
	//	{
	//		GetTranslator(L).pushFunction(L, (LuaCSFunction)o);
	//	}
	//	else if (t.IsSubclassOf(typeof(Delegate)))
	//	{
	//		Push(L, (Delegate)o);
	//	}
	//	else if (IsClassOf(t, typeof(IEnumerator)))
	//	{
	//		Push(L, (IEnumerator)o);
	//	}
	//	else if (t == typeof(string))
	//	{
	//		string str = (string)o;
	//		LuaDLL.lua_pushstring(L, str);
	//	}
	//	else if (t == typeof(LuaStringBuffer))
	//	{
	//		LuaStringBuffer lsb = (LuaStringBuffer)o;
	//		LuaDLL.lua_pushlstring(L, lsb.buffer, lsb.buffer.Length);
	//	}
	//	else if (t.IsSubclassOf(typeof(UnityEngine.Object)))
	//	{
	//		UnityEngine.Object obj = (UnityEngine.Object)o;

	//		if (obj == null)
	//		{
	//			LuaDLL.lua_pushnil(L);
	//		}
	//		else
	//		{
	//			PushObject(L, o);
	//		}
	//	}
	//	else if (t == typeof(LuaTable))
	//	{
	//		((LuaTable)o).push(L);
	//	}
	//	else if (t == typeof(LuaFunction))
	//	{
	//		((LuaFunction)o).push(L);
	//	}
	//	else if (t == monoType)
	//	{
	//		Push(L, (Type)o);
	//	}
	//	else if (t.IsSubclassOf(typeof(TrackedReference)))
	//	{
	//		UnityEngine.TrackedReference obj = (UnityEngine.TrackedReference)o;

	//		if (obj == null)
	//		{
	//			LuaDLL.lua_pushnil(L);
	//		}
	//		else
	//		{
	//			PushObject(L, o);
	//		}
	//	}
	//	else
	//	{
	//		PushObject(L, o);
	//	}
	//}
}

//不缓存LuaFunction
std::vector<LuaCObject*> LuaCVM::CallLuaFunction(std::string name, std::vector<LuaCObject*>& args)
{
	std::vector<LuaCObject*> objs;
	LuaCBase* lb = nullptr;

	if (dict.find(name) != dict.end())
	{
		LuaCFunction* func = (LuaCFunction*)lb;
		return func->Call(args);
	}
	else
	{
		LuaCFunction* func = nullptr;
		int oldTop = lua_gettop(L);

		if (PushLuaFunction(name))
		{
			int reference = luaL_ref(L, LUA_REGISTRYINDEX);
			func = new LuaCFunction(reference, this);
			lua_settop(L, oldTop);
			//std::vector<LuaCObject*> objs = func->Call(args);
			objs = func->Call(args);
			//func.Dispose();
			return objs;
		}

		//return nullptr;
		return objs;
	}
}

//会缓存LuaFunction
LuaCFunction* LuaCVM::GetLuaFunction(std::string name)
{
	LuaCBase* func = nullptr;

	if (dict.find(name) == dict.end())
	{
		func = dict[name];
		int oldTop = lua_gettop(L);

		if (PushLuaFunction(name))
		{
			int reference = luaL_ref(L, LUA_REGISTRYINDEX);
			func = new LuaCFunction(reference, this);
			func->m_name = name;
			dict[name] = func;
		}
		else
		{
			//Debugger.LogError("Lua function {0} not exists", name);
		}

		lua_settop(L, oldTop);
	}
	else
	{
		func->AddRef();
	}

	return (LuaCFunction*)func;
}

int LuaCVM::GetFunctionRef(std::string name)
{
	int oldTop = lua_gettop(L);
	int reference = -1;

	if (PushLuaFunction(name))
	{
		reference = luaL_ref(L, LUA_REGISTRYINDEX);
	}
	else
	{
		//Debugger.LogWarning("Lua function {0} not exists", name);
	}

	lua_settop(L, oldTop);
	return reference;
}

bool LuaCVM::IsFuncExists(std::string name)
{
	int oldTop = lua_gettop(L);

	if (PushLuaFunction(name))
	{
		lua_settop(L, oldTop);
		return true;
	}

	return false;
}

bool LuaCVM::PushLuaFunction(std::string fullPath)
{
	int oldTop = lua_gettop(L);
	int pos = (int)fullPath.find_last_of('.');

	if (pos > 0)
	{
		std::string tableName = fullPath.substr(0, pos);

		if (PushLuaTable(tableName))
		{
			std::string funcName = fullPath.substr(pos + 1);
			lua_pushstring(L, funcName.c_str());
			lua_rawget(L, -2);
		}

		int type = lua_type(L, -1);

		if (type != LUA_TFUNCTION)
		{
			lua_settop(L, oldTop);
			return false;
		}

		lua_insert(L, oldTop + 1);
		lua_settop(L, oldTop + 1);
	}
	else
	{
		lua_getglobal(L, fullPath.c_str());
		int type = lua_type(L, -1);

		if (type != LUA_TFUNCTION)
		{
			lua_settop(L, oldTop);
			return false;
		}
	}

	return true;
}

void LuaCVM::PushTraceBack()
{
#if !MULTI_STATE
	if (traceback == nullptr)
	{
		lua_getglobal(L, "traceback");
		return;
	}

	traceback->push();
#else
	lua_getglobal(L, "traceback");
#endif
}

bool LuaCVM::PushLuaTable(std::string fullPath)
{
	//string[] path = fullPath.Split(new char[] { '.' });
	std::vector<std::string> path;
	std::string delim = ".";
	LuaCUtil::split(fullPath, delim, &path);

	int oldTop = lua_gettop(L);
	// Lua 5.3
	lua_getglobal(L, path[0].c_str());
	// Lua 5.1
	//lua_pushstring(L, path[0].c_str());
	//lua_rawget(L, LUA_GLOBALSINDEX);

	int type = lua_type(L, -1);

	if (type != LUA_TTABLE)
	{
		lua_settop(L, oldTop);
		lua_pushnil(L);
		//Debugger.LogError("Push lua table {0} failed", path[0]);
		return false;
	}

	for (int i = 1; i < path.size(); i++)
	{
		lua_pushstring(L, path[i].c_str());
		lua_rawget(L, -2);
		type = lua_type(L, -1);

		if (type != LUA_TTABLE)
		{
			lua_settop(L, oldTop);
			//Debugger.LogError("Push lua table {0} failed", fullPath);
			return false;
		}
	}

	if (path.size() > 1)
	{
		lua_insert(L, oldTop + 1);
		lua_settop(L, oldTop + 1);
	}

	return true;
}

////压入一个从object派生的变量
//void LuaCVM::PushObject(lua_State* L, object o)
//{
//	GetTranslator(L).pushObject(L, o, "luaNet_metatable");
//}
//
//void LuaCVM::Push(lua_State* L, UnityEngine.Object obj)
//{
//	PushObject(L, obj == null ? null : obj);
//}

void LuaCVM::CreateTable(std::string fullPath)
{
	//string[] path = fullPath.Split(new char[] { '.' });
	std::vector<std::string> path;
	std::string delim = ".";
	LuaCUtil::split(fullPath, delim, &path);

	int oldTop = lua_gettop(L);

	if (path.size() > 1)
	{
		lua_getglobal(L, path[0].c_str());
		int type = lua_type(L, -1);

		if (type == LUA_TNIL)
		{
			lua_pop(L, 1);
			lua_createtable(L, 0, 0);
			// Lua 5.1
			//lua_pushstring(L, path[0].c_str());
			//lua_pushvalue(L, -2);
			//lua_settable(L, LUA_GLOBALSINDEX);
			// Lua 5.3
			lua_pushvalue(L, -1);
			lua_setglobal(L, path[0].c_str());
		}

		for (int i = 1; i < path.size() - 1; i++)
		{
			lua_pushstring(L, path[i].c_str());
			lua_rawget(L, -2);

			type = lua_type(L, -1);

			if (type == LUA_TNIL)
			{
				lua_pop(L, 1);
				lua_createtable(L, 0, 0);
				lua_pushstring(L, path[i].c_str());
				lua_pushvalue(L, -2);
				lua_rawset(L, -4);
			}
		}

		lua_pushstring(L, path[path.size() - 1].c_str());
		lua_rawget(L, -2);

		type = lua_type(L, -1);

		if (type == LUA_TNIL)
		{
			lua_pop(L, 1);
			lua_createtable(L, 0, 0);
			lua_pushstring(L, path[path.size() - 1].c_str());
			lua_pushvalue(L, -2);
			lua_rawset(L, -4);
		}
	}
	else
	{
		lua_getglobal(L, path[0].c_str());
		int type = lua_type(L, -1);

		if (type == LUA_TNIL)
		{
			lua_pop(L, 1);
			lua_createtable(L, 0, 0);
			// Lua 5.1
			//lua_pushstring(L, path[0].c_str());
			//lua_pushvalue(L, -2);
			//lua_settable(L, LUA_GLOBALSINDEX);
			// Lua 5.3
			lua_pushvalue(L, -1);
			lua_setglobal(L, path[0].c_str());
		}
	}

	lua_insert(L, oldTop + 1);
	lua_settop(L, oldTop + 1);
}

void LuaCVM::RegisterLib(std::string libName, std::string className, std::vector<LuaMethod*> regs, std::vector<LuaField*> fields, std::string baseClassName)
{
	CreateTable(libName);

	luaL_getmetatable(L, className.c_str());

	if (lua_isnil(L, -1))
	{
		lua_pop(L, 1);
		luaL_newmetatable(L, className.c_str());
	}

	if (baseClassName.length() > 0)
	{
		//LuaDLL.lua_pushstring(L, "base");
		//LuaDLL.luaL_getmetatable(L, baseType.AssemblyQualifiedName);

		//if (LuaDLL.lua_isnil(L, -1))
		//{
		//    LuaDLL.lua_pop(L, 1);
		//    LuaDLL.luaL_newmetatable(L, baseType.AssemblyQualifiedName);
		//}

		//LuaDLL.lua_rawset(L, -3);

		luaL_getmetatable(L, baseClassName.c_str());

		if (lua_isnil(L, -1))
		{
			lua_pop(L, 1);
			luaL_newmetatable(L, baseClassName.c_str());
			//checkBaseType.Add(baseType);
		}
		else
		{
			//checkBaseType.Remove(baseType);
		}

		lua_setmetatable(L, -2);
	}


	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	//LuaDLL.lua_pushstring(L, "ToLua_Index");
	//LuaDLL.lua_rawget(L, (int)LuaIndexes.LUA_REGISTRYINDEX);                 
	////LuaDLL.lua_pushvalue(L, -2);
	////LuaDLL.lua_pushstdcallcfunction(L, tolua_index, 1);        
	lua_rawset(L, -3);
	//tolua_setindex(L);

	//LuaDLL.lua_pushstring(L, "__newindex");
	//LuaDLL.lua_pushstring(L, "ToLua_NewIndex");
	//LuaDLL.lua_rawget(L, (int)LuaIndexes.LUA_REGISTRYINDEX);            
	////LuaDLL.lua_pushstdcallcfunction(L, NewIndex);
	//LuaDLL.lua_rawset(L, -3);
	//tolua_setnewindex(L);

	//lua_pushstring(L, "__call");
	//lua_pushstring(L, "ToLua_TableCall");
	//lua_rawget(L, LUA_REGISTRYINDEX);
	//lua_rawset(L, -3);

	lua_pushstring(L, "__gc");
	//lua_pushstdcallcfunction(L, __gc);
	lua_pushcfunction(L, garbageCollection);
	lua_rawset(L, -3);

	for (int i = 0; i < regs.size(); i++)
	{
		lua_pushstring(L, regs[i]->name.c_str());
		//lua_pushstdcallcfunction(L, regs[i]->func);
		lua_pushcfunction(L, regs[i]->func);
		lua_rawset(L, -3);
	}

	for (int i = 0; i < fields.size(); i++)
	{
		lua_pushstring(L, fields[i]->name.c_str());
		lua_createtable(L, 2, 0);

		if (fields[i]->getter != nullptr)
		{
			//lua_pushstdcallcfunction(L, fields[i]->getter);
			lua_pushcfunction(L, fields[i]->getter);
			lua_rawseti(L, -2, 1);
		}

		if (fields[i]->setter != nullptr)
		{
			//lua_pushstdcallcfunction(L, fields[i]->setter);
			lua_pushcfunction(L, fields[i]->setter);
			lua_rawseti(L, -2, 2);
		}

		lua_rawset(L, -3);
	}

	lua_setmetatable(L, -2);
	lua_settop(L, 0);

	//checkBaseType.Remove(t);
}

//注册一个枚举类型
void LuaCVM::RegisterLib(std::string libName, std::string className, std::vector<LuaMethod*> regs)
{
	CreateTable(libName);

	luaL_getmetatable(L, className.c_str());

	if (lua_isnil(L, -1))
	{
		lua_pop(L, 1);
		luaL_newmetatable(L, className.c_str());
	}

	lua_pushstring(L, "ToLua_EnumIndex");
	lua_rawget(L, LUA_REGISTRYINDEX);
	lua_setfield(L, -2, "__index");

	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, garbageCollection);
	lua_rawset(L, -3);

	for (int i = 0; i < regs.size() - 1; i++)
	{
		lua_pushstring(L, regs[i]->name.c_str());
		lua_pushcfunction(L, regs[i]->func);
		lua_rawset(L, -3);
	}

	int pos = (int)regs.size() - 1;
	lua_pushstring(L, regs[pos]->name.c_str());
	lua_pushcfunction(L, regs[pos]->func);
	lua_rawset(L, -4);

	lua_setmetatable(L, -2);
	lua_settop(L, 0);
}

void LuaCVM::RegisterLib(std::string libName, std::vector<LuaMethod*> regs)
{
	CreateTable(libName);

	for (int i = 0; i < regs.size(); i++)
	{
		lua_pushstring(L, regs[i]->name.c_str());
		lua_pushcfunction(L, regs[i]->func);
		lua_rawset(L, -3);
	}

	lua_settop(L, 0);
}

int LuaCVM::garbageCollection(lua_State* L)
{
	//int udata = luanet_rawnetobj(luaState, 1);

	//if (udata != -1)
	//{
	//	ObjectTranslator translator = ObjectTranslator.FromState(luaState);
	//	translator.collectObject(udata);
	//}

	return 0;
}

void LuaCVM::ThrowLuaException(lua_State* L)
{
	std::string err = lua_tostring(L, -1);
	if (err.length() == 0) err = "Unknown Lua Error";
	throw new LuaScriptException(err, "");
}

LuaCTable* LuaCVM::GetLuaTable(std::string tableName)
{
	LuaCBase* lt = nullptr;

	if (dict.find(tableName) == dict.end())
	{
		int oldTop = lua_gettop(L);

		if (PushLuaTable(tableName))
		{
			int reference = luaL_ref(L, LUA_REGISTRYINDEX);
			lt = new LuaCTable(reference, this);
			lt->m_name = tableName;
			dict[tableName] = lt;
		}

		lua_settop(L, oldTop);
	}
	else
	{
		lt->AddRef();
	}

	return (LuaCTable*)lt;
}

void LuaCVM::RemoveLuaRes(std::string name)
{
	mapIte ite = dict.find(name);
	if (ite != dict.end())
	{
		dict.erase(ite);
	}
}

double LuaCVM::GetNumber(int stackPos)
{
	if (lua_isnumber(L, stackPos))
	{
		return lua_tonumber(L, stackPos);
	}

	//luaL_typerror(L, stackPos, "number");
	return 0;
}

bool LuaCVM::GetBoolean(int stackPos)
{
	if (lua_isboolean(L, stackPos))
	{
		return lua_toboolean(L, stackPos) != 0;
	}

	//luaL_typerror(L, stackPos, "boolean");
	return false;
}

std::string LuaCVM::GetString(int stackPos)
{
	std::string str = GetLuaString(stackPos);

	if (str == "")
	{
		//luaL_typerror(L, stackPos, "string");
	}

	return str;
}

LuaCFunction* LuaCVM::GetFunction(int stackPos)
{
	int luatype = lua_type(L, stackPos);

	if (luatype != LUA_TFUNCTION)
	{
		return nullptr;
	}

	lua_pushvalue(L, stackPos);
	return new LuaCFunction(luaL_ref(L, LUA_REGISTRYINDEX), GetTranslator()->interpreter);
}

LuaCFunction* LuaCVM::ToLuaFunction(int stackPos)
{
	lua_pushvalue(L, stackPos);
	return new LuaCFunction(luaL_ref(L, LUA_REGISTRYINDEX), GetTranslator()->interpreter);
}

LuaCFunction* LuaCVM::GetLuaFunction(int stackPos)
{
	LuaCFunction* func = GetFunction(stackPos);

	if (func == nullptr)
	{
		//luaL_typerror(L, stackPos, "function");
		return nullptr;
	}

	return func;
}

// 自己添加的函数
//public static LuaTable SelfToLuaTable(IntPtr L, int stackPos)
//{
//    LuaDLL.lua_pushvalue(L, stackPos);
//    return new LuaTable(LuaDLL.luaL_ref(L, LuaIndexes.LUA_REGISTRYINDEX), GetTranslator(L).interpreter);
//}

LuaCTable* LuaCVM::ToLuaTable(int stackPos)
{
	lua_pushvalue(L, stackPos);
	return new LuaCTable(luaL_ref(L, LUA_REGISTRYINDEX), GetTranslator()->interpreter);
}

LuaCTable* LuaCVM::GetTable(int stackPos)
{
	int luatype = lua_type(L, stackPos);

	if (luatype != LUA_TTABLE)
	{
		return nullptr;
	}

	lua_pushvalue(L, stackPos);
	return new LuaCTable(luaL_ref(L, LUA_REGISTRYINDEX), GetTranslator()->interpreter);
}

LuaCTable* LuaCVM::GetLuaTable(int stackPos)
{
	LuaCTable* table = GetTable(stackPos);

	if (table == nullptr)
	{
		//luaL_typerror(L, stackPos, "table");
		return nullptr;
	}

	return table;
}

//注册到lua中的object类型对象, 存放在ObjectTranslator objects 池中
LuaCObject* LuaCVM::GetLuaObject(int stackPos)
{
	//return GetTranslator(L)->getRawNetObject(L, stackPos);
	return nullptr;
}

std::string LuaCVM::GetLuaString(int stackPos)
{
	int luatype = lua_type(L, stackPos);
	std::stringstream strStream;
	std::string retVal = "";

	if (luatype == LUA_TSTRING)
	{
		retVal = lua_tostring(L, stackPos);
	}
	else if (luatype == LUA_TUSERDATA)
	{
		LuaCObject* obj = GetLuaObject(stackPos);

		if (obj == nullptr)
		{
			luaL_argerror(L, stackPos, "string expected, got nil");
			return "";
		}

		if (obj->GetType() == LUAC_TSTRING)
		{
			retVal = obj->m_pChar;
		}
		else
		{
			//retVal = obj.ToString();
			retVal = "aaa";
		}
	}
	else if (luatype == LUA_TNUMBER)
	{
		double d = lua_tonumber(L, stackPos);
		strStream << d;
		retVal = strStream.str();
	}
	else if (luatype == LUA_TBOOLEAN)
	{
		bool b = lua_toboolean(L, stackPos) != 0;
		strStream << b;
		retVal = strStream.str();
	}
	else if (luatype == LUA_TNIL)
	{
		return retVal;
	}
	else
	{
		lua_getglobal(L, "tostring");
		lua_pushvalue(L, stackPos);
		lua_call(L, 1, 1);
		retVal = lua_tostring(L, -1);
		lua_pop(L, 1);
	}

	return retVal;
}

lua_State* LuaCVM::GetL()
{
	return L;
}