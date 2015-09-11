#ifndef _XmlConfig_H
#define _XmlConfig_H

#include <string>	// include string
#include <vector>	// include vector
#include "tinyxml2.h"	// include xml
#include "EnValue.h"
#include "TabelAttr.h"

// import namespace
//using namespace std;
//using namespace tinyxml2;

#include "Platform.h"

BEGIN_NAMESPACE

// 输出文件的类型，主要用来区别平台的
#define OUT_TYPE_CLIENT "client"
#define OUT_TYPE_SERVER "server"

/**
* @brief field 字段
*/
class XmlField
{
public:
	std::string m_fieldName;		// 字段名字
	std::string m_fieldType;		// 字段类型
	int m_fieldSize;				// 字段占用内存大小
	int m_fieldBase;				// 字段进制， 二进制、八进制、十进制
	std::string m_defaultValue;		// 默认值
	std::string m_codeName;			// 导出代码需要的变量名字

public:
	XmlField();
	~XmlField();

	std::string getCodeName();
	std::string getFieldType();
	int getFieldSize();
};


class Package;

/**
* @brief Table 内容
*/
class Table
{
public:
	// 这些数据一定要申请内存，然后拷贝过来的
	std::string m_lpszTableName;		// tbl文件名称本身，输出的表的名字，包括扩展名字，没有路径
	std::string m_lpszExcelFile;		// Excel文件名字和扩展名字（不包括路径）
	std::string m_lpszDB;				// 数据库
	std::string m_lpszDBTableName;		// 数据库中表的名字
	std::string m_lpszOutputFile;		// tbl文件的全路径（包括文件名称）
	std::string m_lpId;					// id 过滤字段
	std::string m_lpszCodeFileName;		// 代码输出的文件名字
	std::string m_outType;				// 输出表的内容，例如 Client、Server 等

	std::string m_strOutput;			// 临时的表的描述输出字段
	TableAttr m_tableAttr;				// 定义的表的属性

	std::string m_strStructDef;			// 表的结构体描述
	std::string m_strExcelDir;			// Excel 文件所在的目录
	std::string m_strExcelDirAndName;	// Excel 文件的目录和名字

	EnExcelType m_enExcelType;			// 当前编辑的文件是 xls 还是 xlsx
	bool m_bExportTable;				// 是否导出这个表
	bool m_bRecStructDef;				// 是否需要生成表的定义

	std::vector<XmlField*> m_fieldsList;
	Package* m_pPackage;
	std::string m_className;			// 输出代码的类的名字

public:
	Table();
	~Table();

	std::vector<XmlField*>& getFieldsList();
	void clearFieldsList();

	Package* getPackagePtr();
	void setPackagePtr(Package* pPackage);

	std::string getCodeFileName();
	std::string getClassName();

	void parseXML(tinyxml2::XMLElement* pXmlEmtFields);
	bool buildTableDefine();
	bool isExportClientTable();		// 是否是导出客户端表

	void exportCode();		// 导出代码
	void exportExcel();		// 导出 Excel
};

class Solution;

/**
* @brief package a table
*/
class Package
{
protected:
	std::string m_xml;		// xml path + name
	std::string m_output;	// output path
	std::vector<Table*> m_tablesList;		// 保存包中 Xml 配置列表，可能只有一个，也可能有多个
	Solution* m_pSolution;

public:
	Package();
	~Package();

	std::string getXml();
	std::string getOutput();

	std::vector<Table*>& getTablesList();
	void clearTablesList();					// 清理内容

	Solution* getSolutionPtr();
	void setSolution(Solution* pSolution);

	void setXml(std::string xml);
	void setOutput(std::string output);
	void initByXml(tinyxml2::XMLElement* elem);
	bool loadTableXml();
	void destroy();

	void exportCode();		// 导出代码
	void exportExcel();		// 导出 Excel
};


/**
* @brief one solution
*/
class Solution
{
protected:
	std::string m_name;				// solution name
	std::string m_cmd;				// excute cmd, usually is a bat file
	std::string m_xmlRootPath;		// Xml 文件根目录
	std::string m_defaultOutput;		// 默认的输出目录
	std::vector<Package*> m_lstPack;	// need pack list

	std::string m_cppOutPath;			// C++ 输出目录
	std::string m_csOutPath;			// CS 输出目录
	std::vector<Table*> m_tablesList;	// Solution 包括的 Package 中的所有的 table 的列表

public:
	Solution();
	~Solution();

	std::string getName();
	std::string getCmd();

	std::string getCppOutPath();
	std::string getCsOutPath();

	std::vector<Table*>& getTablesList();
	void clearTablesList();

	void setName(std::string name);
	void setCmd(std::string cmd);
	void initByXml(tinyxml2::XMLElement* elem);
	std::vector<Package*>& getPackLst();
	void loadTableXml();
	void destroy();

	void exportCode();		// 导出代码
	void exportExcel();		// 导出 Excel
};

END_NAMESPACE

#endif