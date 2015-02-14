#ifndef _PROPERTYSTR_H
#define _PROPERTYSTR_H

#include "PropertyIns.hxx"
#include <string>

#include "Platform.hxx"
BEGIN_NAMESPACE

class PropertyStr : public PropertyIns<std::string>
{
public:
	size_t m_cfgLen;			// ���ñ��еĳ���

protected:
	virtual void srz2BU(ByteBuffer& byteBuffer);

public:
	// ���л� web
	virtual void srz2BUWeb(ByteBuffer& byteBuffer);
	// ���л��ƶ��豸
	virtual void srz2BUMobile(ByteBuffer& byteBuffer);
};

END_NAMESPACE

#endif	// _PROPERTYSTR_H  