#ifndef _PROPERTYINS_H
#define _PROPERTYINS_H

#include "PropertyBase.hxx"
#include "ByteBuffer.hxx"
#include "Platform.hxx"

BEGIN_NAMESPACE

// ����� string ֮��� CBO 
template <class T>
class PropertyIns : public PropertyBase
{
public:
	T m_propData;

protected:
	virtual void srz2BU(ByteBuffer& byteBuffer)
	{
		byteBuffer.append<T>(&m_propData, 1);		// ����ط�ֱ��ʹ��
	}

public:
	// ���л�������
	virtual void srz2BUServer(ByteBuffer& byteBuffer)
	{
		srz2BU(byteBuffer);
	}

	// ���л�����ͻ���
	virtual void srz2BUDesktop(ByteBuffer& byteBuffer)
	{
		srz2BU(byteBuffer);
	}

	// ���л� web
	virtual void srz2BUWeb(ByteBuffer& byteBuffer)
	{
		srz2BU(byteBuffer);
	}

	// ���л��ƶ��豸
	virtual void srz2BUMobile(ByteBuffer& byteBuffer)
	{
		srz2BU(byteBuffer);
	}
};

END_NAMESPACE

#endif	// _PROPERTYINS_H 