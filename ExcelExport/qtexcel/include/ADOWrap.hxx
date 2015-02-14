#ifndef _ADOWRAP_H
#define _ADOWRAP_H

#include "Platform.hxx"
#include <string>

#import "C:\Program Files\Common Files\System\ado\msado15.dll" \
	no_namespace rename("EOF","adoEOF") \
	rename("BOF","adoBOF")

BEGIN_NAMESPACE

class Table;

class ADOWrap
{
public:
	// ���һ��ָ��Connection�����ָ��
	_ConnectionPtr m_pConnection;
	// ���һ��ָ��Recordset �����ָ��
	_RecordsetPtr m_pRecordset;
	// �ܵļ�¼����    
	int m_count;	// ���ݱ����ܵ����� 

public:
	ADOWrap();
	~ADOWrap();

	bool opemDB(Table* tableItem);
	void closeDB();
	bool isAdoEOF();
	void moveNext();

	unsigned int getCollectUInt(std::string fieldName);
	_variant_t getCollect(const char* fieldName);
};

END_NAMESPACE

#endif