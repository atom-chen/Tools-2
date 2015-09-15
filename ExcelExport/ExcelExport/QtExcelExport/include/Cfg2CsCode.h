#ifndef __Cfg2CsCode_h
#define __Cfg2CsCode_h

#include "Platform.h"
#include "Cfg2Code.h"
#include <string>
#include <map>

BEGIN_NAMESPACE

class CsKeyWordMap
{
public:
	std::string m_typeName;
	std::string m_readFunc;
};

/**
*@brief 转换配置文件到代码
*/
class Cfg2CsCode : public Cfg2Code
{
public:
	static std::map<eBaseType, CsKeyWordMap> m_sKW2CsKW;
	static void initKWMap();
	static CsKeyWordMap& convKW2CsKW(std::string fieldType, int fieldSize);

public:
	Cfg2CsCode();
	~Cfg2CsCode();
	virtual void exportCode();
};

END_NAMESPACE

#endif