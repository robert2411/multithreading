/*
 *	This file contains the windows inplementation of the threading class
 */
#ifdef _WIN32
#include <windows.h>
#include "thread.h"

DWORD Thread::ThreadRunner(LPVOID lpParam)
{
	Thread* p_thread = (Thread*) lpParam;

	p_thread->mp_function(p_thread->mp_param);

	return TRUE;
}

int Thread::Start()
{
	if (mp_function == NULL)
		return THREAD_ERROR_FUNCTION_POINTER_NULL;

	m_thread = CreateThread( 
            NULL,							// default security attributes
            0,								// use default stack size  
            ThreadRunner,					// thread function name
            (void*) this,					// argument to thread function
            0,								// use default creation flags 
            &m_threadId);					// returns the thread identifier 
	return 0;
}

int Thread::Stop()
{
	if (m_thread == NULL)
		return THREAD_ERROR_NO_RUNNING_THREAD;

	if(!TerminateThread(m_thread, 0))
		return THREAD_ERROR_CANT_CLOSE_THREAD;

	m_thread = NULL;
	m_threadId = 0;
	return 0;
}

Thread::~Thread()
{
	Stop();
	CloseHandle(m_thread);
}
#endif