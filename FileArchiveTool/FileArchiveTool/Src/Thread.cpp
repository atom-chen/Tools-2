#ifdef WIN32
#include <windows.h>
#endif

#include "Thread.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

Thread::Thread()
	: m_exitFlag(false)
{
	m_iThreadId = new boost::thread::id;
	m_ThreadImp = new std::auto_ptr<boost::thread>;
}

Thread::~Thread()
{
	delete m_iThreadId;
	delete m_ThreadImp;
}

void Thread::Start()
{
	m_ThreadImp->reset(new boost::thread(boost::bind(&Thread::ThreadTask, this)));
	*m_iThreadId = (*m_ThreadImp)->get_id();
}

bool Thread::Wait()
{
    if (*m_iThreadId == boost::thread::id())
        return false;

    bool res = true;

	if (m_ThreadImp->get())
	{
		try
		{
			(*m_ThreadImp)->join();
		}
		catch (boost::thread_interrupted&)
		{
			res = false;
		}

		m_ThreadImp->reset();
	}

    *m_iThreadId = boost::thread::id();

    return res;
}

void Thread::destroy()
{
    if (*m_iThreadId == boost::thread::id())
        return;

    (*m_ThreadImp)->interrupt();
    *m_iThreadId = boost::thread::id();
}

void Thread::ThreadTask(void* param)
{
	Thread* _task = (Thread*)param;
    _task->run();
}

boost::thread::id Thread::currentId()
{
    return boost::this_thread::get_id();
}

void Thread::setPriority(Priority priority)
{
    boost::thread::native_handle_type handle = (*m_ThreadImp)->native_handle();
    bool _ok = true;

#ifdef WIN32

    switch (priority)
    {
		case Priority_Realtime:
		{
			_ok = SetThreadPriority(handle, THREAD_PRIORITY_TIME_CRITICAL) != 0; 
			break;
		}
		case Priority_Highest:
		{
			_ok = SetThreadPriority(handle, THREAD_PRIORITY_HIGHEST) != 0;       
			break;
		}
		case Priority_High:
		{
			_ok = SetThreadPriority(handle, THREAD_PRIORITY_ABOVE_NORMAL) != 0;  
			break;
		}
		case Priority_Normal:
		{
			_ok = SetThreadPriority(handle, THREAD_PRIORITY_NORMAL) != 0;        
			break;
		}
		case Priority_Low:
		{
			_ok = SetThreadPriority(handle, THREAD_PRIORITY_BELOW_NORMAL) != 0;  
			break;
		}
		case Priority_Lowest:
		{
			_ok = SetThreadPriority(handle, THREAD_PRIORITY_LOWEST) != 0;        
			break;
		}
		case Priority_Idle:
		{
			_ok = SetThreadPriority(handle, THREAD_PRIORITY_IDLE) != 0;          
			break;
		}
    }

#endif
}

void Thread::Sleep(unsigned long msecs)
{
    boost::this_thread::sleep(boost::posix_time::milliseconds(msecs));
}

void Thread::setExitFlag(bool exit)
{
	m_exitFlag = exit;
}

END_NAMESPACE_FILEARCHIVETOOL