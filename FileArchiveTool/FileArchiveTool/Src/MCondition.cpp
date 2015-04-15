#include "MCondition.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

MCondition::MCondition()
{
	m_NotifyLock = new boost::mutex;
	m_pNotifyCond = new boost::condition;
	m_canEnterWait = true;      // �������ȴ�״̬
}

MCondition::~MCondition()
{
	delete m_NotifyLock;
	delete m_pNotifyCond;
}

bool MCondition::canEnterWait()
{
	return m_canEnterWait;
}

void MCondition::wait()
{
	boost::mutex::scoped_lock sl(*m_NotifyLock);
	if (m_canEnterWait)
	{
		m_pNotifyCond->wait(*m_NotifyLock);	// ����
	}
	else
	{
		m_canEnterWait = true;
	}
}

void MCondition::notifyOne()
{
	boost::mutex::scoped_lock sl(*m_NotifyLock);

	if (m_canEnterWait) // ��� m_canEnterWait == false����Ȼ���ܽ���ȴ�
	{
		m_canEnterWait = false;
		m_pNotifyCond->notify_one();		// ����һ��
	}
}

void MCondition::notifyAll()
{
	boost::mutex::scoped_lock sl(*m_NotifyLock);

	if (m_canEnterWait) // ��� m_canEnterWait == false����Ȼ���ܽ���ȴ�
	{
		m_canEnterWait = false;
		m_pNotifyCond->notify_all();
	}
}

END_NAMESPACE_FILEARCHIVETOOL