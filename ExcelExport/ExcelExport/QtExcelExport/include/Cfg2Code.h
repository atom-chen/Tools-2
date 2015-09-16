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
	eInt8 = 0,
	eUInt8 = 1,
	eInt16 = 2,
	eUInt16 = 3,
	eInt32 = 4,
	eUInt32 = 5,
	eInt64 = 6,
	eUInt64 = 7,
	eFloat = 8,
	eDouble = 9,
	eString = 10,
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