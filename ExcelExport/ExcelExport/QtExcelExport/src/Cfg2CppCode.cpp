#include "Cfg2CppCode.h"
#include <string>
#include <sstream>
#include "XmlConfig.h"
#include <stdio.h>

BEGIN_NAMESPACE

//std::map<std::string, std::string> Cfg2CppCode::m_sKW2CppKW;

//void Cfg2CppCode::initKWMap()
//{
//	m_sKW2CppKW[""] = ""
//}

std::string Cfg2CppCode::convKW2CppKW(std::string fieldType, int fieldSize)
{
	if (INT_KW == fieldType)
	{
		if (1 == fieldSize)
		{
			return "BYTE";
		}
		if (2 == fieldSize)
		{
			return "WORD";
		}
		if (3 == fieldSize)
		{
			return "DWORD";
		}
		if (4 == fieldSize)
		{
			return "QWORD";
		}
	}
	else if (FLOAT_KW == fieldType)
	{
		if (4 == fieldSize)
		{
			return "float";
		}
		else if (8 == fieldSize)
		{
			return "double";
		}
	}
	else if (STRING_KW == fieldType)
	{
		return "char";
	}

	return "BYTE";
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

	strStream << "class " << m_pTable->getClassName();
	strStream << "\n" << "{";
	strStream << "\n" << "public:";

	for (auto field : m_pTable->getFieldsList())
	{
		strStream << "\n" << "\t" << convKW2CppKW(field->getFieldType(), field->getFieldSize()) << " " << field->getCodeName();
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