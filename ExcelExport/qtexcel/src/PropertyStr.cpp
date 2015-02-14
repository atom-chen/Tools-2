#include "PropertyStr.hxx"

void PropertyStr::srz2BU(ByteBuffer& byteBuffer)
{
	byteBuffer.writeMultiByte(m_propData.c_str(), m_cfgLen);
}

void PropertyStr::srz2BUWeb(ByteBuffer& byteBuffer)
{
	if (m_cfgLen >= m_propData.size())
	{
		byteBuffer.writeUnsignedInt16((uint16)m_propData.size());	// д��ʵ�ʳ���
		byteBuffer.writeMultiByte(m_propData.c_str(), m_propData.size());
	}
	else
	{
		byteBuffer.writeUnsignedInt16((uint16)m_cfgLen);	// д��ʵ�ʳ���
		byteBuffer.writeMultiByte(m_propData.c_str(), m_cfgLen);
	}
}

void PropertyStr::srz2BUMobile(ByteBuffer& byteBuffer)
{
	srz2BUWeb(byteBuffer);
}