#ifndef __Cfg2CsCode_h
#define __Cfg2CsCode_h

#include "Platform.h"
#include "Cfg2Code.h"

BEGIN_NAMESPACE

/**
*@brief ת�������ļ�������
*/
class Cfg2CsCode : public Cfg2Code
{
protected:


public:
	Cfg2CsCode();
	~Cfg2CsCode();
	virtual void exportCode();
};

END_NAMESPACE

#endif