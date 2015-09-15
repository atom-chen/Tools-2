#include "Cfg2CsCode.h"
#include <string>
#include <sstream>
#include "XmlConfig.h"
#include <stdio.h>

BEGIN_NAMESPACE

std::map<eBaseType, CsKeyWordMap> Cfg2CsCode::m_sKW2CsKW;

void Cfg2CsCode::initKWMap()
{
	m_sKW2CsKW[eInt8] = CsKeyWordMap();
	m_sKW2CsKW[eInt8].m_typeName = "byte";
	m_sKW2CsKW[eInt8].m_readFunc = "readInt8";

	m_sKW2CsKW[eUInt8] = CsKeyWordMap();
	m_sKW2CsKW[eUInt8].m_typeName = "byte";
	m_sKW2CsKW[eUInt8].m_readFunc = "readUnsignedInt8";

	m_sKW2CsKW[eInt16] = CsKeyWordMap();
	m_sKW2CsKW[eInt16].m_typeName = "ushort";
	m_sKW2CsKW[eInt16].m_readFunc = "readInt16";

	m_sKW2CsKW[eUInt16] = CsKeyWordMap();
	m_sKW2CsKW[eUInt16].m_typeName = "ushort";
	m_sKW2CsKW[eUInt16].m_readFunc = "readUnsignedInt16";

	m_sKW2CsKW[eInt32] = CsKeyWordMap();
	m_sKW2CsKW[eInt32].m_typeName = "uint";
	m_sKW2CsKW[eInt32].m_readFunc = "readInt32";

	m_sKW2CsKW[eUInt32] = CsKeyWordMap();
	m_sKW2CsKW[eUInt32].m_typeName = "uint";
	m_sKW2CsKW[eUInt32].m_readFunc = "readUnsignedInt32";

	m_sKW2CsKW[eInt64] = CsKeyWordMap();
	m_sKW2CsKW[eInt64].m_typeName = "long";
	m_sKW2CsKW[eInt64].m_readFunc = "readInt64";

	m_sKW2CsKW[eUInt64] = CsKeyWordMap();
	m_sKW2CsKW[eUInt64].m_typeName = "ulong";
	m_sKW2CsKW[eInt8].m_readFunc = "readUnsignedInt64";

	m_sKW2CsKW[eFloat] = CsKeyWordMap();
	m_sKW2CsKW[eFloat].m_typeName = "float";
	m_sKW2CsKW[eFloat].m_readFunc = "readFloat";

	m_sKW2CsKW[eDouble] = CsKeyWordMap();
	m_sKW2CsKW[eDouble].m_typeName = "double";
	m_sKW2CsKW[eDouble].m_readFunc = "readDouble";

	m_sKW2CsKW[eString] = CsKeyWordMap();
	m_sKW2CsKW[eString].m_typeName = "string";
	m_sKW2CsKW[eString].m_readFunc = "UtilTable.readString";
}

CsKeyWordMap& Cfg2CsCode::convKW2CsKW(std::string fieldType, int fieldSize)
{
	if (INT_KW == fieldType)
	{
		if (1 == fieldSize)
		{
			return m_sKW2CsKW[eUInt8];
		}
		if (2 == fieldSize)
		{
			return m_sKW2CsKW[eUInt16];
		}
		if (4 == fieldSize)
		{
			return m_sKW2CsKW[eUInt32];
		}
		if (8 == fieldSize)
		{
			return m_sKW2CsKW[eUInt64];
		}
	}
	else if (FLOAT_KW == fieldType)
	{
		if (4 == fieldSize)
		{
			return m_sKW2CsKW[eFloat];
		}
		else if (8 == fieldSize)
		{
			return m_sKW2CsKW[eDouble];
		}
	}
	else if (STRING_KW == fieldType)
	{
		return m_sKW2CsKW[eString];
	}

	return m_sKW2CsKW[eUInt8];
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

	strStream.str("");		// 清空内容
	strStream.clear();

	strStream << "namespace SDK.Lib";
	strStream << "\n" << "{";
	strStream << "\n" << "\t" <<"public class " << m_pTable->getClassName() << " : TableItemBodyBase";
	strStream << "\n" << "\t" << "{";

	// 输出字段列表
	for (auto field : m_pTable->getFieldsList())
	{
		strStream << "\n" << "\t\t" << "public " << convKW2CsKW(field->getFieldType(), field->getFieldSize()).m_typeName << " " << field->getCodeName() << ";";
	}

	// 输出字段序列化
	strStream << "\n";
	strStream << "\n" << "\t\t" << "override public void parseBodyByteBuffer(ByteBuffer bytes, uint offset)";
	strStream << "\n" << "\t\t";
	strStream << "\n" << "\t\t\t" << "bytes.position = offset;";
	for (auto field : m_pTable->getFieldsList())
	{
		if (field->isStringField())
		{
			strStream << "\n" << "\t\t\t" << "UtilTable.readString(bytes, ref " << field->getCodeName() << ")";
		}
		else
		{
			strStream << "\n" << "\t\t\t" << "bytes." << convKW2CsKW(field->getFieldType(), field->getFieldSize()).m_readFunc << "(ref " << field->getCodeName() << ")";
		}
	}

	strStream << "\n" << "}";
	fwrite(strStream.str().c_str(), strStream.str().length(), 1, fp);

	fclose(fp);
}

END_NAMESPACE