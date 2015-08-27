#ifndef __LuaCBridge_H_
#define __LuaCBridge_H_

#include "lua.hpp"
#include <string>

/**
 *@brief ��ʾһ�� Lua �е�ģ�飬һ�����е����ݣ����ϲ������еĹ���
 */
class LuaCBridge
{
	std::string m_bridgeName;		// ���� Lua �� C ֮��ı�����

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

#endif