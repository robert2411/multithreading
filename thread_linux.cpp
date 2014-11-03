/*
 *	This file contains the linux inplementation of the threading class
 */
#ifdef __linux__
#include "thread.h"
void* Thread::ThreadRunner(void* ptr)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	Thread* p_thread = (Thread*) ptr;
	p_thread->mp_function(p_thread->mp_param);
}

int Thread::Start()
{
	int iret;
	if (mp_function == NULL)
		return THREAD_ERROR_FUNCTION_POINTER_NULL;

	 iret = pthread_create( &m_thread, NULL, ThreadRunner, (void*) this);
     if(iret)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret);
         return THREAD_ERROR_CANT_START_THREAD;
     }
	return 0;
}

int Thread::Stop()
{
	if (m_thread == 0)
		return THREAD_ERROR_NO_RUNNING_THREAD;

	if(!pthread_cancel((m_thread)))
		return THREAD_ERROR_CANT_CLOSE_THREAD;

	m_thread = 0;
	m_threadId = 0;
	return 0;
}

Thread::~Thread()
{
	Stop();
	//CloseHandle(m_thread);
}
#endif

