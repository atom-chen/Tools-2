#ifndef __LuaScriptMgr_H_
#define __LuaScriptMgr_H_

class LuaCVM;

/**
 *@brief �ű�����������Ӧһ�������
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