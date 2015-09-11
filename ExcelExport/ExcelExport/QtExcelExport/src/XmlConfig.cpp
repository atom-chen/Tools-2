#include "XmlConfig.h"
#include "AppSysPrerequisites.h"
#include "tinyxml2.h"
#include <direct.h>		// chdir
#include <string.h>
#include <stdio.h>

#include "MemLeakCheck.h"

BEGIN_NAMESPACE

XmlField::XmlField()
{
	m_fieldSize = -1;
	m_fieldBase = 10;	// ������ʲô
	m_defaultValue = "10";
}

Table::Table()
{
	m_bExportTable = false;
	m_bRecStructDef = true;
}

void Table::parseXML(tinyxml2::XMLElement* pXmlEmtFields)
{
	XmlField* fieldItem;
	tinyxml2::XMLElement* field = pXmlEmtFields->FirstChildElement("field");
	while (field)
	{
		fieldItem = new XmlField();
		m_fieldsList.push_back(fieldItem);

		fieldItem->m_fieldName = Utils::copyPChar2Str(field->Attribute("name"));
		fieldItem->m_fieldType = Utils::copyPChar2Str(field->Attribute("type"));

		// ��� field �� string ���ͣ�size ���ó��Ȱ�����β�� 0 
		if (field->QueryIntAttribute("size", &fieldItem->m_fieldSize) != tinyxml2::XML_SUCCESS)
		{
			fieldItem->m_fieldSize = -1;
		}
		if (field->QueryIntAttribute("base", &fieldItem->m_fieldBase) != tinyxml2::XML_SUCCESS)
		{
			fieldItem->m_fieldBase = 10;
		}

		fieldItem->m_defaultValue = Utils::copyPChar2Str(field->Attribute("default"));
		// Ĭ�ϵ����� 
		if (0 == fieldItem->m_fieldType.length())
		{
			fieldItem->m_fieldType = "int";
		}
		field = field->NextSiblingElement("field");
	}
}

bool Table::buildTableDefine()
{
	m_strStructDef = "struct  ";
	m_strStructDef += m_lpszTableName;
	m_strStructDef += "{\r\n";

	int iFieldNum = 0;
	int iFieldIndex = 0;

	XmlField* field;
	char szMsg[256];

	while (iFieldIndex < m_fieldsList.size())
	{
		field = m_fieldsList[iFieldIndex];
		const char* fieldName = field->m_fieldName.c_str();
		const char* fieldType = field->m_fieldType.c_str();

		int fieldSize = -1;
		int fieldBase = 10;	// ������ʲô 
		const char* defaultValue = "10";

		fieldSize = field->m_fieldSize;
		fieldBase = field->m_fieldBase;

		defaultValue = field->m_defaultValue.c_str();
		// Ĭ�ϵ����� 
		if (fieldType == NULL)
		{
			fieldType = "int";
		}

		if (fieldName && fieldType)
		{
			if (stricmp(fieldType, "string") == 0)
			{
				memset(szMsg, 0, sizeof(szMsg));
				sprintf(szMsg, "\tchar\tstrField%d[%d];\t\t// %s\r\n", iFieldNum++, fieldSize, fieldName);
				m_strStructDef += szMsg;
			}
			else if (stricmp(fieldType, "int") == 0)
			{
				if (fieldSize == -1)
				{
					fieldSize = 4;
				}

				memset(szMsg, 0, sizeof(szMsg));

				switch (fieldSize)
				{
				case 1:
				{
					sprintf(szMsg, "\tBYTE\tbyField%d;\t\t// %s\r\n", iFieldNum++, fieldName);
				}
				break;
				case 2:
				{
					sprintf(szMsg, "\tWORD\twdField%d;\t\t// %s\r\n", iFieldNum++, fieldName);
				}
				break;
				case 4:
				{
					sprintf(szMsg, "\tDWORD\tdwField%d;\t\t// %s\r\n", iFieldNum++, fieldName);
				}
				break;
				case 8:
				{
					sprintf(szMsg, "\tQWORD\tqwField%d;\t\t// %s\r\n", iFieldNum++, fieldName);
				}
				break;
				}

				m_strStructDef += szMsg;
			}
			else if (stricmp(fieldType, "float") == 0)
			{
				if (fieldSize == -1)
				{
					fieldSize = 4;
				}

				memset(szMsg, 0, sizeof(szMsg));

				switch (fieldSize)
				{
				case 4:
				{
					sprintf(szMsg, "\tfloat\tfField%d;\t\t// %s\r\n", iFieldNum++, fieldName);
				}
				break;
				case 8:
				{
					sprintf(szMsg, "\tdouble\tdField%d;\t\t// %s\r\n", iFieldNum++, fieldName);
				}
				break;
				}

				m_strStructDef += szMsg;
			}
		}
		iFieldIndex++;
	}
	// һ��֮��Ͳ�������ṹ��
	m_bRecStructDef = false;

	m_strStructDef += "};";

	return true;
}

// �Ƿ��ǵ����ͻ��˱�
bool Table::isExportClientTable()
{
	//if (-1 != m_lpszTableName.find("client"))
	if (m_outType == OUT_TYPE_CLIENT)
	{
		return true;
	}

	return false;
}

Package::Package()
{

}

Package::~Package()
{
	clearTablesList();
}

std::string Package::getXml()
{
	return m_xml;
}

std::string Package::getOutput()
{
	return m_output;
}

void Package::setXml(std::string xml)
{
	m_xml = xml;
}

void Package::setOutput(std::string output)
{
	m_output = output;
}

std::vector<Table*>& Package::getTablesList()
{
	return m_tablesList;
}

void Package::clearTablesList()
{
	for (auto table : m_tablesList)
	{
		delete table;
	}

	m_tablesList.clear();
}

void Package::initByXml(tinyxml2::XMLElement* elem)
{
	m_xml = elem->Attribute("xml");
	m_output = elem->Attribute("output");
}

void Package::destroy()
{
	clearTablesList();
}

bool Package::loadTableXml()
{
	Table* tableItem;

	std::string::size_type iTmp;
	iTmp = m_xml.find_last_of('\\');
	if (iTmp == -1)
	{
		iTmp = m_xml.find_last_of('/');
	}

	try
	{
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLElement* config = NULL;
		tinyxml2::XMLElement* table = NULL;

		if (doc.LoadFile(m_xml.c_str()) != tinyxml2::XML_SUCCESS)
		{
			throw "xml����ʧ��!";
		}
		config = doc.FirstChildElement("config");
		if (!config)
		{
			throw "xml�ļ�û��config��ǩ";
		}

		table = config->FirstChildElement("table");
		if (!table)
		{
			throw "xml�ļ�û��table��ǩ";
		}

		while (table)
		{
			tableItem = new Table();
			m_tablesList.push_back(tableItem);

			tableItem->m_strExcelDir = m_xml.substr(0, iTmp);
			if (_chdir(tableItem->m_strExcelDir.c_str()) == -1)			// ��鵱ǰĿ¼�Ƿ����
			{
				QString msg = "��ǰĿ¼������ȷ";
				g_pUtils->informationMessage(NULL, msg);
			}

			if (m_output.empty())
			{
				m_output = tableItem->m_strExcelDir;
			}

			tinyxml2::XMLElement* field;

			tableItem->m_lpszTableName = Utils::copyPChar2Str(table->Attribute("name"));
			tableItem->m_lpszExcelFile = Utils::copyPChar2Str(table->Attribute("ExcelFile"));
			tableItem->m_lpszDB = Utils::copyPChar2Str(table->Attribute("db"));
			tableItem->m_lpszDBTableName = Utils::copyPChar2Str(table->Attribute("tablename"));		// ��������
			tableItem->m_outType = Utils::copyPChar2Str(table->Attribute("outtype"));				// ���������
			tableItem->m_lpszCodeFileName = Utils::copyPChar2Str(table->Attribute("codefilename"));	// ���������ļ�����

			// �������õ� ID ��Χ
			tableItem->m_lpId = Utils::copyPChar2Str(table->Attribute("idrange"));
			if (tableItem->m_lpId.c_str())
			{
				tableItem->m_tableAttr.parseInRange(tableItem->m_lpId);
			}

			tableItem->m_lpszOutputFile = m_output + "/" + tableItem->m_lpszTableName;
			tableItem->m_strOutput += "//---------------------\r\n";
			tableItem->m_strOutput += "//";

			tableItem->m_strOutput += tableItem->m_lpszTableName;
			tableItem->m_strOutput += "\r\n";
			tableItem->m_strOutput += "//---------------------\r\n";
			tableItem->m_strStructDef = "";
			tableItem->m_strExcelDirAndName = tableItem->m_strExcelDir + "/" + tableItem->m_lpszExcelFile;
			if (stricmp("xls", g_pUtils->GetFileNameExt(tableItem->m_lpszExcelFile.c_str()).c_str()) == 0)
			{
				tableItem->m_enExcelType = eXLS;
			}
			else if (stricmp("xlsx", g_pUtils->GetFileNameExt(tableItem->m_lpszExcelFile.c_str()).c_str()) == 0)
			{
				tableItem->m_enExcelType = eXLSX;
			}
			else
			{
				QString tmpmsg = QStringLiteral("���ܶ�ȡ����ļ���ʽ�ı��, �ļ� ");
				tmpmsg += tableItem->m_lpszExcelFile.c_str();
				g_pUtils->informationMessage(tmpmsg);
			}

			field = table->FirstChildElement("fields");
			tableItem->parseXML(field);			// ��ȡ�������
			tableItem->buildTableDefine();		// ���ɱ�Ķ���

			tableItem->m_strOutput += tableItem->m_strStructDef.c_str();
			tableItem->m_strOutput += "\r\n";
			table = table->NextSiblingElement("table");
		}
	}
	catch (const char* p)
	{
		g_pUtils->informationMessage(g_pUtils->LocalChar2UNICODEStr(p));
		return false;
	}
	catch (...)
	{
		g_pUtils->informationMessage(QStringLiteral("�����쳣"));
		return false;
	}

	return true;
}



Solution::Solution()
{

}

Solution::~Solution()
{
	clearTablesList();
}

std::string Solution::getName()
{
	return m_name;
}

std::string Solution::getCmd()
{
	return m_cmd;
}

void Solution::setName(std::string name)
{
	m_name = name;
}

void Solution::setCmd(std::string cmd)
{
	m_cmd = cmd;
}

std::string Solution::getCppOutPath()
{
	return m_cppOutPath;
}

std::string Solution::getCsOutPath()
{
	return m_csOutPath;
}

std::vector<Table*>& Solution::getTablesList()
{
	return m_tablesList;
}

void Solution::clearTablesList()
{
	m_tablesList.clear();				// ����������Ǳ���������ã���Ҫ���������ͷ� table ָ��
}

std::vector<Package*>& Solution::getPackLst()
{
	return m_lstPack;
}

void Solution::initByXml(tinyxml2::XMLElement* elem)
{
	tinyxml2::XMLElement* packageXml = NULL;
	Package* ppackage;

	packageXml = elem->FirstChildElement("package");
	m_name = elem->Attribute("name");
	m_cmd = elem->Attribute("cmd");
	m_xmlRootPath = elem->Attribute("xmlrootpath");
	m_defaultOutput = elem->Attribute("defaultoutput");
	m_cppOutPath = elem->Attribute("cppoutpath");
	m_csOutPath = elem->Attribute("csoutpath");

	// ת��Ŀ¼������Ŀ¼
	g_pUtils->convToAbsPath(m_xmlRootPath);
	g_pUtils->convToAbsPath(m_defaultOutput);

	while (packageXml)
	{
		ppackage = new Package();
		m_lstPack.push_back(ppackage);
		ppackage->initByXml(packageXml);

		// ���û���������
		//if (ppackage->getOutput() == nullptr || ppackage->getOutput().length == 0)
		if (ppackage->getOutput().length() == 0)
		{
			ppackage->setOutput(m_defaultOutput);
		}

		if (ppackage->getXml().find(':') == -1)	// ��������Ŀ¼
		{
			ppackage->setXml(m_xmlRootPath + "/" + ppackage->getXml());
		}

		packageXml = packageXml->NextSiblingElement("package");
	}
}

void Solution::loadTableXml()
{
	std::vector<Package*>::iterator packIteVecBegin;
	std::vector<Package*>::iterator packIteVecEnd;

	packIteVecBegin = m_lstPack.begin();
	packIteVecEnd = m_lstPack.end();

	for (; packIteVecBegin != packIteVecEnd; ++packIteVecBegin)
	{
		(*packIteVecBegin)->loadTableXml();
	}
}

void Solution::destroy()
{

}


END_NAMESPACE