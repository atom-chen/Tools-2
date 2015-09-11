#ifndef __Cfg2Code_h
#define __Cfg2Code_h

#include "Platform.h"

BEGIN_NAMESPACE

// ��������м����ؼ�������
#define INT_KW "int"
#define FLOAT_KW "float"
#define STRING_KW "string"

class Table;

/**
*@brief ת�������ļ�������
*/
class Cfg2Code
{
protected:
	Table* m_pTable;

public:
	Cfg2Code();
	~Cfg2Code();

	void setTable(Table* pm_pTable);
	virtual void exportCode();		// �����õ�������
};

END_NAMESPACE

#endif