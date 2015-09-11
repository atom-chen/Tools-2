#ifndef __Cfg2Code_h
#define __Cfg2Code_h

#include "Platform.h"

BEGIN_NAMESPACE

class Solution;
class Package;

/**
*@brief ת�������ļ�������
*/
class Cfg2Code
{
protected:
	Solution* m_pSolution;
	Package* m_pPackage;

public:
	Cfg2Code();
	~Cfg2Code();

	void setSolution(Solution* pSolution);
	void setPackage(Package* pPackage);

	virtual void exportCode();		// �����õ�������
};

END_NAMESPACE

#endif