#ifndef _PROPERTYBASE_H
#define _PROPERTYBASE_H

#include "ByteBuffer.hxx"
#include "Platform.hxx"

BEGIN_NAMESPACE

class PropertyBase
{
public:
	bool m_isIDField;			// ָ���Ƿ��� id �ֶΣ� ����� id �ֶν��������⴦��

public:
	PropertyBase()
	{
		m_isIDField = false;
	}

	virtual ~PropertyBase()
	{

	}

protected:
	// �����ͨ�����л�
	virtual void srz2BU(ByteBuffer& byteBuffer) = 0;

public:
	// ���л�������
	virtual void srz2BUServer(ByteBuffer& byteBuffer) = 0;
	// ���л�����ͻ���
	virtual void srz2BUDesktop(ByteBuffer& byteBuffer) = 0;
	// ���л� web
	virtual void srz2BUWeb(ByteBuffer& byteBuffer) = 0;
	// ���л��ƶ��豸
	virtual void srz2BUMobile(ByteBuffer& byteBuffer) = 0;
};

END_NAMESPACE

#endif	// _PROPERTYBASE_H  