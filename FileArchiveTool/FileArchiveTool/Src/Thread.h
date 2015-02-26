#ifndef THREADING_H
#define THREADING_H

#include <boost/atomic.hpp>
#include <boost/thread.hpp>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

enum Priority
{
    Priority_Idle,
    Priority_Lowest,
    Priority_Low,
    Priority_Normal,
    Priority_High,
    Priority_Highest,
    Priority_Realtime,
};

class Thread : public boost::noncopyable
{
protected:
	bool m_exitFlag;
	boost::thread::id m_iThreadId;
	std::auto_ptr<boost::thread> m_ThreadImp;

public:
    Thread();
    virtual ~Thread();

	void Start();
    bool Wait();
    void destroy();	// Ç¿ÖÆÍË³ö

    void setPriority(Priority type);
	void setExitFlag(bool exit);

    static void Sleep(unsigned long msecs);
    static boost::thread::id currentId();

private:
    static void ThreadTask(void* param);
	virtual void run() = 0;
};

END_NAMESPACE_FILEARCHIVETOOL

#endif
