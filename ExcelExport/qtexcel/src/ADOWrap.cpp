#include "ADOWrap.hxx"
#include "CTask.hxx"
#include "Tools.hxx"

ADOWrap::ADOWrap()
{
	m_count = 0;
}

ADOWrap::~ADOWrap()
{
	closeDB();
}

bool ADOWrap::opemDB(Table* tableItem)
{
	const char* provider;					// ���������ṩ��
	const char* extendedProperties;			// ��չ����

	if (eXLS == tableItem->m_enExcelType)
	{
		provider = XLS_ENGINE_provider;
		extendedProperties = XLS_ENGINE_extendedProperties;
	}
	else
	{
		provider = XLSX_ENGINE_provider;
		extendedProperties = XLSX_ENGINE_extendedProperties;
	}

	// com �ӿڳ�ʼ��    
	// ��һ���������     
	_bstr_t _table_name;
	// �����ݿ���ַ��� 
	_bstr_t _strConnect;
	// �򿪱���ַ���   
	_bstr_t _bstrSQL;

	::CoInitialize(NULL);
	_table_name = tableItem->m_lpszDBTableName.c_str();

	// �����ݿ�    
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		_strConnect += provider;
		_strConnect += "Data Source=";
		_strConnect += tableItem->m_strExcelDirAndName.c_str();
		_strConnect += ";";
		_strConnect += extendedProperties;

		m_pConnection->Open(_strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)		//��׽�쳣		
	{
		::CoUninitialize();
		Tools::getSingletonPtr()->informationMessage(QStringLiteral("�����ݿⷢ���쳣"));
		return false;
	}

	// �򿪵�һ����   
	try
	{
		m_pRecordset.CreateInstance(_uuidof(Recordset));

		_bstrSQL += "SELECT * FROM ";
		_bstrSQL += "[";
		_bstrSQL += _table_name;
		_bstrSQL += "$]";

		// ��֤ GetRecordCount ������ȷ�Ľ��  
		m_pRecordset->CursorLocation = adUseClient;
		m_pRecordset->Open(_bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

		// ��ȡ��¼�������� 
		m_count = m_pRecordset->GetRecordCount();
	}
	catch (_com_error e)
	{
		m_pConnection->Close();
		::CoUninitialize();
		Tools::getSingletonPtr()->informationMessage(QStringLiteral("�����ݿ�ĵ�һ�������쳣"));

		return false;
	}

	return true;
}

bool ADOWrap::isAdoEOF()
{
	return (m_pRecordset->adoEOF == -1);
}

void ADOWrap::moveNext()
{
	m_pRecordset->MoveNext();
}

unsigned int ADOWrap::getCollectUInt(std::string fieldName)
{
	return m_pRecordset->GetCollect((_variant_t)(fieldName.c_str())).uintVal;
}

_variant_t ADOWrap::getCollect(const char* fieldName)
{
	return m_pRecordset->GetCollect((_variant_t)fieldName);
}

void ADOWrap::closeDB()
{
	m_pRecordset->Close();
	m_pConnection->Close();
	::CoUninitialize();
}