#ifndef __Cfg2CppCode_h
#define __Cfg2CppCode_h

#include "Platform.h"
#include "Cfg2Code.h"

BEGIN_NAMESPACE

/**
*@brief ת�������ļ�������
*/
class Cfg2CppCode : public Cfg2Code
{
protected:

public:
	Cfg2CppCode();
	~Cfg2CppCode();
	virtual void exportCode();
};

END_NAMESPACE

#endif