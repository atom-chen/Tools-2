#ifndef __LuaScriptMgr_H_
#define __LuaScriptMgr_H_

class LuaCVM;

/**
 *@brief 脚本管理器，对应一个虚拟机
 */
class LuaCScriptMgr
{
public:
	static LuaCScriptMgr* Instance;

protected:
	LuaCVM* m_pLuaCVM;

public:
	LuaCScriptMgr();
	~LuaCScriptMgr();

	LuaCVM* getLuaCVM();
};

#endif