#ifndef __Cfg2CppCode_h
#define __Cfg2CppCode_h

#include "Platform.h"
#include "Cfg2Code.h"
#include <map>
#include <string>

BEGIN_NAMESPACE

class CppKeyWordMap
{
public:
	std::string m_typeName;
};

/**
*@brief 转换配置文件到代码
*/
class Cfg2CppCode : public Cfg2Code
{
public:
	static std::map<eBaseType, CppKeyWordMap> m_sKW2CppKW;
	static void initKWMap();
	static CppKeyWordMap& convKW2CppKW(std::string fieldType, int fieldSize);

protected:

public:
	Cfg2CppCode();
	~Cfg2CppCode();
	virtual void exportCode();
};

END_NAMESPACE

#endif