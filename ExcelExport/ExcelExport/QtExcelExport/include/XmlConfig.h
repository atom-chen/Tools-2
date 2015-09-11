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

// ����ļ������ͣ���Ҫ��������ƽ̨��
#define OUT_TYPE_CLIENT "client"
#define OUT_TYPE_SERVER "server"

/**
* @brief field �ֶ�
*/
class XmlField
{
public:
	std::string m_fieldName;		// �ֶ�����
	std::string m_fieldType;		// �ֶ�����
	int m_fieldSize;				// �ֶ�ռ���ڴ��С
	int m_fieldBase;				// �ֶν��ƣ� �����ơ��˽��ơ�ʮ����
	std::string m_defaultValue;		// Ĭ��ֵ
	std::string m_codeName;			// ����������Ҫ�ı�������

public:
	XmlField();
	~XmlField();

	std::string getCodeName();
	std::string getFieldType();
	int getFieldSize();
};


class Package;

/**
* @brief Table ����
*/
class Table
{
public:
	// ��Щ����һ��Ҫ�����ڴ棬Ȼ�󿽱�������
	std::string m_lpszTableName;		// tbl�ļ����Ʊ�������ı�����֣�������չ���֣�û��·��
	std::string m_lpszExcelFile;		// Excel�ļ����ֺ���չ���֣�������·����
	std::string m_lpszDB;				// ���ݿ�
	std::string m_lpszDBTableName;		// ���ݿ��б������
	std::string m_lpszOutputFile;		// tbl�ļ���ȫ·���������ļ����ƣ�
	std::string m_lpId;					// id �����ֶ�
	std::string m_lpszCodeFileName;		// ����������ļ�����
	std::string m_outType;				// ���������ݣ����� Client��Server ��

	std::string m_strOutput;			// ��ʱ�ı����������ֶ�
	TableAttr m_tableAttr;				// ����ı������

	std::string m_strStructDef;			// ��Ľṹ������
	std::string m_strExcelDir;			// Excel �ļ����ڵ�Ŀ¼
	std::string m_strExcelDirAndName;	// Excel �ļ���Ŀ¼������

	EnExcelType m_enExcelType;			// ��ǰ�༭���ļ��� xls ���� xlsx
	bool m_bExportTable;				// �Ƿ񵼳������
	bool m_bRecStructDef;				// �Ƿ���Ҫ���ɱ�Ķ���

	std::vector<XmlField*> m_fieldsList;
	Package* m_pPackage;
	std::string m_className;			// ���������������

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
	bool isExportClientTable();		// �Ƿ��ǵ����ͻ��˱�

	void exportCode();		// ��������
	void exportExcel();		// ���� Excel
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
	std::vector<Table*> m_tablesList;		// ������� Xml �����б�����ֻ��һ����Ҳ�����ж��
	Solution* m_pSolution;

public:
	Package();
	~Package();

	std::string getXml();
	std::string getOutput();

	std::vector<Table*>& getTablesList();
	void clearTablesList();					// ��������

	Solution* getSolutionPtr();
	void setSolution(Solution* pSolution);

	void setXml(std::string xml);
	void setOutput(std::string output);
	void initByXml(tinyxml2::XMLElement* elem);
	bool loadTableXml();
	void destroy();

	void exportCode();		// ��������
	void exportExcel();		// ���� Excel
};


/**
* @brief one solution
*/
class Solution
{
protected:
	std::string m_name;				// solution name
	std::string m_cmd;				// excute cmd, usually is a bat file
	std::string m_xmlRootPath;		// Xml �ļ���Ŀ¼
	std::string m_defaultOutput;		// Ĭ�ϵ����Ŀ¼
	std::vector<Package*> m_lstPack;	// need pack list

	std::string m_cppOutPath;			// C++ ���Ŀ¼
	std::string m_csOutPath;			// CS ���Ŀ¼
	std::vector<Table*> m_tablesList;	// Solution ������ Package �е����е� table ���б�

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

	void exportCode();		// ��������
	void exportExcel();		// ���� Excel
};

END_NAMESPACE

#endif