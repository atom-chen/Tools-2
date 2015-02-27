﻿#ifndef _CTASK_H
#define _CTASK_H

#include <string>	// include string
#include <vector>	// include vector
#include "tinyxml2.h"	// include xml
#include "EnValue.hxx"
#include "TabelAttr.hxx"

// import namespace
using namespace std;
//using namespace tinyxml2;

#include "Platform.hxx"
BEGIN_NAMESPACE

/**
* @brief field 字段
*/
class XmlField
{
public:
	std::string m_fieldName;
	std::string m_fieldType;
	int m_fieldSize;
	int m_fieldBase;
	std::string m_defaultValue;

public:
	XmlField();
};

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
	std::string m_lpId;			// id 过滤字段

	string m_strOutput;			// 临时的表的描述输出字段
	TableAttr m_tableAttr;		// 定义的表的属性

	std::string m_strStructDef;			// 表的结构体描述
	std::string m_strExcelDir;			// Excel 文件所在的目录
	std::string m_strExcelDirAndName;	// Excel 文件的目录和名字

	EnExcelType m_enExcelType;
	bool m_bExportTable;			// 是否导出这个表
	bool m_bRecStructDef;			// 是否需要生成表的定义

	std::vector<XmlField*> m_fieldsList;

public:
	Table();
	void parseXML(tinyxml2::XMLElement* pXmlEmtFields);
	bool buildTableDefine();

	bool isExportClientTable();		// 是否是导出客户端表
};

/**
 * @brief package a table
 */
class CPackage
{
protected:
	string m_xml;		// xml path + name
	string m_output;	// output path

public:
	CPackage();
	~CPackage();

	string getXml();
	string getOutput();

	void setXml(string xml);
	void setOutput(string output);
	void initByXml(tinyxml2::XMLElement* elem);
	bool loadTableXml(std::vector<Table*>& tablesList);
	void destroy();
};


/**
 * @brief one solution
 */
class CSolution
{
protected:
	string m_name;		// solution name
	string m_cmd;		// excute cmd, usually is a bat file
	string m_xmlRootPath;		// Xml 文件根目录
	string m_defaultOutput;		// 默认的输出目录
	vector<CPackage*> m_lstPack;	// need pack list

public:
	CSolution();
	~CSolution();

	string getName();
	string getCmd();

	void setName(string name);
	void setCmd(string cmd);
	void initByXml(tinyxml2::XMLElement* elem);
	vector<CPackage*>& getPackLst();
	void loadTableXml(std::vector<Table*>& tablesList);
	void destroy();
};

/**
 * @brief task
 */
class CTask
{
protected:
	CSolution* m_pSolution;
	std::vector<Table*> m_tablesList;

public:
	CTask();
	~CTask();

	CSolution* getSolution();
	void readXML();		// read config.xml
	void destroy();

	std::vector<Table*>& getTableList();
};

END_NAMESPACE

#endif