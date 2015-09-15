#include "XmlConfig.h"
#include "AppSysPrerequisites.h"
#include "tinyxml2.h"
#include <direct.h>		// chdir
#include <string.h>
#include <stdio.h>
#include "Cfg2Code.h"
#include "Cfg2CppCode.h"
#include "Cfg2CsCode.h"
#include "MemLeakCheck.h"
#include "ExcelExport.h"

BEGIN_NAMESPACE

XmlField::XmlField()
{
	m_fieldSize = -1;
	m_fieldBase = 10;	// 进制是什么
	m_defaultValue = "10";
}

XmlField::~XmlField()
{

}

std::string XmlField::getCodeName()
{
	return m_codeName;
}

std::string XmlField::getFieldType()
{
	return m_fieldType;
}

bool XmlField::isStringField()
{
	return m_fieldType == STRING_KW;
}

int XmlField::getFieldSize()
{
	return m_fieldSize;
}

void XmlField::parseXML(tinyxml2::XMLElement* field)
{
	this->m_fieldName = Utils::copyPChar2Str(field->Attribute("name"));
	this->m_fieldType = Utils::copyPChar2Str(field->Attribute("type"));
	this->m_codeName = Utils::copyPChar2Str(field->Attribute("codename"));

	// 如果 field 是 string 类型，size 配置长度包括结尾符 0 
	if (field->QueryIntAttribute("size", &this->m_fieldSize) != tinyxml2::XML_SUCCESS)
	{
		this->m_fieldSize = -1;
	}
	if (field->QueryIntAttribute("base", &this->m_fieldBase) != tinyxml2::XML_SUCCESS)
	{
		this->m_fieldBase = 10;
	}

	this->m_defaultValue = Utils::copyPChar2Str(field->Attribute("default"));
	// 默认的类型 
	if (0 == this->m_fieldType.length())
	{
		this->m_fieldType = "int";
	}
}



Table::Table()
{
	m_bExportTable = false;
	m_bRecStructDef = true;
}

Table::~Table()
{
	clearFieldsList();
}

std::vector<XmlField*>& Table::getFieldsList()
{
	return m_fieldsList;
}

void Table::clearFieldsList()
{
	for (auto field : m_fieldsList)
	{
		delete field;
	}

	m_fieldsList.clear();
}

Package* Table::getPackagePtr()
{
	return m_pPackage;
}

void Table::setPackagePtr(Package* pPackage)
{
	m_pPackage = pPackage;
}

std::string Table::getCodeFileName()
{
	return m_lpszCodeFileName;
}

std::string Table::getClassName()
{
	return m_className;
}

void Table::parseXML(tinyxml2::XMLElement* pXmlEmtFields)
{
	XmlField* fieldItem;
	tinyxml2::XMLElement* field = pXmlEmtFields->FirstChildElement("field");
	while (field)
	{
		fieldItem = new XmlField();
		m_fieldsList.push_back(fieldItem);
		fieldItem->parseXML(field);
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
		int fieldBase = 10;	// 进制是什么 
		const char* defaultValue = "10";

		fieldSize = field->m_fieldSize;
		fieldBase = field->m_fieldBase;

		defaultValue = field->m_defaultValue.c_str();
		// 默认的类型 
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
	// 一次之后就不在输出结构了
	m_bRecStructDef = false;

	m_strStructDef += "};";

	return true;
}

// 是否是导出客户端表
bool Table::isExportClientTable()
{
	//if (-1 != m_lpszTableName.find("client"))
	if (m_outType == OUT_TYPE_CLIENT)
	{
		return true;
	}

	return false;
}

void Table::setExportClientTable(bool bExportTable)
{
	m_bExportTable = bExportTable;
}

void Table::exportCppCode()
{
	if (this->m_bExportTable)
	{
		Cfg2Code* pCfg2Code = new Cfg2CppCode();
		pCfg2Code->setTable(this);
		pCfg2Code->exportCode();
		delete pCfg2Code;
	}
}

void Table::exportCsCode()
{
	if (this->m_bExportTable)
	{
		Cfg2Code* pCfg2Code = new Cfg2CsCode();
		pCfg2Code->setTable(this);
		pCfg2Code->exportCode();
		delete pCfg2Code;
	}
}

void Table::exportExcel()
{
	if (this->m_bExportTable)
	{
		g_pExcelExport->exportExcelByTable(this);
	}
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

Solution* Package::getSolutionPtr()
{
	return m_pSolution;
}

void Package::setSolution(Solution* pSolution)
{
	m_pSolution = pSolution;
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

void Package::setAllExportClientTable()
{
	for (auto table : m_tablesList)
	{
		table->setExportClientTable(true);
	}
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
			throw "xml加载失败!";
		}
		config = doc.FirstChildElement("config");
		if (!config)
		{
			throw "xml文件没有config标签";
		}

		table = config->FirstChildElement("table");
		if (!table)
		{
			throw "xml文件没有table标签";
		}

		while (table)
		{
			tableItem = new Table();
			tableItem->setPackagePtr(this);
			m_tablesList.push_back(tableItem);

			tableItem->m_strExcelDir = m_xml.substr(0, iTmp);
			if (_chdir(tableItem->m_strExcelDir.c_str()) == -1)			// 检查当前目录是否存在
			{
				QString msg = "当前目录设置正确";
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
			tableItem->m_lpszDBTableName = Utils::copyPChar2Str(table->Attribute("tablename"));		// 表单的名字
			tableItem->m_outType = Utils::copyPChar2Str(table->Attribute("outtype"));				// 输出的类型
			tableItem->m_lpszCodeFileName = Utils::copyPChar2Str(table->Attribute("codefilename"));	// 输出代码的文件名字
			tableItem->m_className = Utils::copyPChar2Str(table->Attribute("classname"));		// 输出的类的名字

			// 表中配置的 ID 范围
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
				QString tmpmsg = QStringLiteral("不能读取这个文件格式的表格, 文件 ");
				tmpmsg += tableItem->m_lpszExcelFile.c_str();
				g_pUtils->informationMessage(tmpmsg);
			}

			field = table->FirstChildElement("fields");
			tableItem->parseXML(field);			// 读取表的属性
			tableItem->buildTableDefine();		// 生成表的定义

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
		g_pUtils->informationMessage(QStringLiteral("意外异常"));
		return false;
	}

	return true;
}

void Package::exportCppCode()
{
	for (auto table : m_tablesList)
	{
		table->exportCppCode();
	}
}

void Package::exportCsCode()
{
	for (auto table : m_tablesList)
	{
		table->exportCsCode();
	}
}

void Package::exportExcel()
{
	for (auto table : m_tablesList)
	{
		table->exportExcel();
	}
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
	m_tablesList.clear();				// 这里面仅仅是保存的是引用，不要在这里面释放 table 指针
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

	// 转换目录到绝对目录
	g_pUtils->convToAbsPath(m_xmlRootPath);
	g_pUtils->convToAbsPath(m_defaultOutput);
	g_pUtils->convToAbsPath(m_cppOutPath);
	g_pUtils->convToAbsPath(m_csOutPath);

	while (packageXml)
	{
		ppackage = new Package();
		ppackage->setSolution(this);
		m_lstPack.push_back(ppackage);
		ppackage->initByXml(packageXml);

		// 如果没有配置输出
		//if (ppackage->getOutput() == nullptr || ppackage->getOutput().length == 0)
		if (ppackage->getOutput().length() == 0)
		{
			ppackage->setOutput(m_defaultOutput);
		}

		if (ppackage->getXml().find(':') == -1)	// 如果是相对目录
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
		m_tablesList.insert(m_tablesList.end(), (*packIteVecBegin)->getTablesList().begin(), (*packIteVecBegin)->getTablesList().end());
	}
}

void Solution::destroy()
{
	clearTablesList();
}

void Solution::exportCppCode()
{
	for (auto package : m_lstPack)
	{
		package->exportCppCode();
	}
}

void Solution::exportCsCode()
{
	for (auto package : m_lstPack)
	{
		package->exportCsCode();
	}
}

void Solution::exportExcel()
{
	for (auto package : m_lstPack)
	{
		package->exportExcel();
	}
}


END_NAMESPACE