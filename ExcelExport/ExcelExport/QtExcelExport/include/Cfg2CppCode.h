#ifndef __Cfg2CppCode_h
#define __Cfg2CppCode_h

#include "Platform.h"
#include "Cfg2Code.h"
#include <map>
#include <string>

BEGIN_NAMESPACE

/**
*@brief 转换配置文件到代码
*/
class Cfg2CppCode : public Cfg2Code
{
public:
	//static std::map<std::string, std::string> m_sKW2CppKW;
	//static void initKWMap();
	static std::string convKW2CppKW(std::string fieldType, int fieldSize);

protected:

public:
	Cfg2CppCode();
	~Cfg2CppCode();
	virtual void exportCode();
};

END_NAMESPACE

#endif