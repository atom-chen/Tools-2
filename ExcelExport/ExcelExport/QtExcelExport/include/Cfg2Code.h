#ifndef __Cfg2Code_h
#define __Cfg2Code_h

#include "Platform.h"

BEGIN_NAMESPACE

// 打表配置中几个关键字类型
#define INT_KW "int"
#define FLOAT_KW "float"
#define STRING_KW "string"

class Table;

/**
*@brief 转换配置文件到代码
*/
class Cfg2Code
{
protected:
	Table* m_pTable;

public:
	Cfg2Code();
	~Cfg2Code();

	void setTable(Table* pm_pTable);
	virtual void exportCode();		// 从配置导出代码
};

END_NAMESPACE

#endif