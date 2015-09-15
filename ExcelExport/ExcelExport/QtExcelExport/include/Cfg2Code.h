#ifndef __Cfg2Code_h
#define __Cfg2Code_h

#include "Platform.h"

BEGIN_NAMESPACE

// ��������м����ؼ�������
#define INT_KW "int"
#define FLOAT_KW "float"
#define STRING_KW "string"

class Table;

enum eBaseType
{
	eInt8,
	eUInt8,
	eInt16,
	eUInt16,
	eInt32,
	eUInt32,
	eInt64,
	eUInt64,
	eFloat,
	eDouble,
	eString,
};

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