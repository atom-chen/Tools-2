#include "Cfg2CppCode.h"
#include <string>
#include <sstream>
#include "XmlConfig.h"
#include <stdio.h>

BEGIN_NAMESPACE

std::map<eBaseType, CppKeyWordMap> Cfg2CppCode::m_sKW2CppKW;

void Cfg2CppCode::initKWMap()
{
	m_sKW2CppKW[eInt8] = CppKeyWordMap();
	m_sKW2CppKW[eInt8].m_typeName = "BYTE";

	m_sKW2CppKW[eUInt8] = CppKeyWordMap();
	m_sKW2CppKW[eUInt8].m_typeName = "BYTE";

	m_sKW2CppKW[eInt16] = CppKeyWordMap();
	m_sKW2CppKW[eInt16].m_typeName = "WORD";

	m_sKW2CppKW[eUInt16] = CppKeyWordMap();
	m_sKW2CppKW[eUInt16].m_typeName = "WORD";

	m_sKW2CppKW[eInt32] = CppKeyWordMap();
	m_sKW2CppKW[eInt32].m_typeName = "DWORD";

	m_sKW2CppKW[eUInt32] = CppKeyWordMap();
	m_sKW2CppKW[eUInt32].m_typeName = "DWORD";

	m_sKW2CppKW[eInt64] = CppKeyWordMap();
	m_sKW2CppKW[eInt64].m_typeName = "QWORD";

	m_sKW2CppKW[eUInt64] = CppKeyWordMap();
	m_sKW2CppKW[eUInt64].m_typeName = "QWORD";

	m_sKW2CppKW[eFloat] = CppKeyWordMap();
	m_sKW2CppKW[eFloat].m_typeName = "float";

	m_sKW2CppKW[eDouble] = CppKeyWordMap();
	m_sKW2CppKW[eDouble].m_typeName = "double";

	m_sKW2CppKW[eString] = CppKeyWordMap();
	m_sKW2CppKW[eString].m_typeName = "char";
}

CppKeyWordMap& Cfg2CppCode::convKW2CppKW(std::string fieldType, int fieldSize)
{
	if (INT_KW == fieldType)
	{
		if (1 == fieldSize)
		{
			return m_sKW2CppKW[eUInt8];
		}
		if (2 == fieldSize)
		{
			return m_sKW2CppKW[eUInt16];
		}
		if (4 == fieldSize)
		{
			return m_sKW2CppKW[eUInt32];
		}
		if (8 == fieldSize)
		{
			return m_sKW2CppKW[eUInt64];
		}
	}
	else if (FLOAT_KW == fieldType)
	{
		if (4 == fieldSize)
		{
			return m_sKW2CppKW[eFloat];
		}
		else if (8 == fieldSize)
		{
			return m_sKW2CppKW[eDouble];
		}
	}
	else if (STRING_KW == fieldType)
	{
		return m_sKW2CppKW[eString];
	}

	return m_sKW2CppKW[eUInt8];
}

Cfg2CppCode::Cfg2CppCode()
{

}

Cfg2CppCode::~Cfg2CppCode()
{

}

void Cfg2CppCode::exportCode()
{
	std::stringstream strStream;
	strStream << m_pTable->getPackagePtr()->getSolutionPtr()->getCppOutPath() << "/" << m_pTable->getCodeFileName();

	FILE * fp;
	fp = fopen(strStream.str().c_str(), "w");
	if (fp == nullptr)
	{
		return;
	}

	strStream.str("");		// 清空内容
	strStream.clear();

	strStream << "struct " << m_pTable->getClassName();
	strStream << "\n" << "{";
	//strStream << "\n" << "public:";

	for (auto field : m_pTable->getFieldsList())
	{
		strStream << "\n" << "\t" << convKW2CppKW(field->getFieldType(), field->getFieldSize()).m_typeName << " " << field->getCodeName();
		if (STRING_KW == field->getFieldType())			// 如果是字符串
		{
			strStream << "[" << field->getFieldSize() << "];";
		}
		else
		{
			strStream << ";";
		}
	}

	strStream << "\n" << "};";
	fwrite(strStream.str().c_str(), strStream.str().length(), 1, fp);

	fclose(fp);
}

END_NAMESPACE