#ifndef __LuaCBridge_H_
#define __LuaCBridge_H_

#include "GameEditor.h"
#include "lua.hpp"
#include <string>

BEGIN_NAMESPACE_GAMEEDITOR

/**
 *@brief ��ʾһ�� Lua �е�ģ�飬һ�����е����ݣ����ϲ������еĹ���
 */
class GAMEEDITOR_EXPORT LuaCBridge
{
#include "PushWarn.h"
	std::string m_bridgeName;		// ���� Lua �� C ֮��ı�����
#include "PopWarn.h"

public:
	LuaCBridge();
	~LuaCBridge();

	void callFunction(const char* funcName_);
	void callGlobalFunction(const char* funcName_);
	void getFunction(const char* funcName_);
	void getGlobalFunction(const char* funcName_);
	void getData(const char* dataName_);
	void getGlobalData(const char* dataName_);
};

END_NAMESPACE_GAMEEDITOR

#endif