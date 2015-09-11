#include "Cfg2CsCode.h"
#include <string>
#include <sstream>
#include "XmlConfig.h"
#include <stdio.h>

BEGIN_NAMESPACE

std::string Cfg2CsCode::convKW2CppKW(std::string fieldType, int fieldSize)
{
	if (INT_KW == fieldType)
	{
		if (1 == fieldSize)
		{
			return "byte";
		}
		if (2 == fieldSize)
		{
			return "ushort";
		}
		if (3 == fieldSize)
		{
			return "uint";
		}
		if (4 == fieldSize)
		{
			return "long";
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
		return "string";
	}

	return "BYTE";
}

Cfg2CsCode::Cfg2CsCode()
{

}

Cfg2CsCode::~Cfg2CsCode()
{

}

void Cfg2CsCode::exportCode()
{
	std::stringstream strStream;
	strStream << m_pTable->getPackagePtr()->getSolutionPtr()->getCppOutPath() << "/" << m_pTable->getCodeFileName();

	FILE * fp;
	fp = fopen(strStream.str().c_str(), "w");
	if (fp == nullptr)
	{
		return;
	}

	strStream.str("");		// Çå¿ÕÄÚÈÝ
	strStream.clear();

	strStream << "public class " << m_pTable->getClassName();
	strStream << "\n" << "{";

	for (auto field : m_pTable->getFieldsList())
	{
		strStream << "\n" << "\t" << "public " << convKW2CppKW(field->getFieldType(), field->getFieldSize()) << " " << field->getCodeName() << ";";
	}

	strStream << "\n" << "}";
	fwrite(strStream.str().c_str(), strStream.str().length(), 1, fp);

	fclose(fp);
}

END_NAMESPACE