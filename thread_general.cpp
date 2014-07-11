/*
 *	All the general functions for the threading class can be found here
 */
#include "thread.h"

Thread::Thread()
{
	mp_param = NULL;
	mp_function = NULL;

#ifdef _WIN32
	m_thread = NULL;
	m_threadId = 0;
#endif
}

int Thread::SetThreadFunction(int (*p_function)(void*) )
{
	if (p_function == NULL)
		return THREAD_ERROR_FUNCTION_POINTER_NULL;
	mp_function = p_function;
	return 0;
}

int Thread::SetParam(void* p_param)
{
		if (p_param == NULL)
			return THREAD_ERROR_PARAM_POINTER_NULL;
		mp_param = p_param;
		return 0;
}
