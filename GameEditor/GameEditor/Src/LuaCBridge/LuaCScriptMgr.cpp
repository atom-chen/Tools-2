#include "LuaCScriptMgr.h"
#include <sstream>
#include "LuaCVM.h"

BEGIN_NAMESPACE_GAMEEDITOR

LuaCScriptMgr::LuaCScriptMgr()
{
	m_pLuaCVM = new LuaCVM;
	setLuaFilePath("D:/file/opensource/unity-game-git/unitygame/Tools/GameEditor/LuaScript");
	luaL_dofile(m_pLuaCVM->m_L, "TestLua.lua");
}

LuaCScriptMgr::~LuaCScriptMgr()
{
	m_pLuaCVM->closeLua();
}

void LuaCScriptMgr::setLuaFilePath(std::string path)
{
	std::stringstream strStream;
	strStream << "local m_package_path = package.path" << "\r\n" << "package.path = string.format(\"%s;%s/?.lua\", m_package_path, " << path << ")";
	luaL_dostring(m_pLuaCVM->m_L, strStream.str().c_str());
}

void LuaCScriptMgr::setCFilePath(std::string path)
{

}

END_NAMESPACE_GAMEEDITOR