#ifndef __Cfg2CsCode_h
#define __Cfg2CsCode_h

#include "Platform.h"
#include "Cfg2Code.h"
#include <string>

BEGIN_NAMESPACE

/**
*@brief 转换配置文件到代码
*/
class Cfg2CsCode : public Cfg2Code
{
public:
	static std::string convKW2CppKW(std::string fieldType, int fieldSize);

protected:


public:
	Cfg2CsCode();
	~Cfg2CsCode();
	virtual void exportCode();
};

END_NAMESPACE

#endif