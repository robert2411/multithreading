#ifdef _WIN32
#include "mutex.h"

Mutex::Mutex()
{
	m_mutex = CreateMutex( 
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex
}

int Mutex::Lock()
{
	DWORD dwWaitResult;
	dwWaitResult = WaitForSingleObject( 
		m_mutex,    // handle to mutex
		INFINITE);  // no time-out interval

	if (dwWaitResult == WAIT_OBJECT_0 )
		return 0;

	if (dwWaitResult == WAIT_ABANDONED)
		return MUTEX_ERROR_LOCK_WAIT_ABANDONED;

	return MUTEX_ERROR_LOCK_ERROR;

}

int Mutex::Unlock()
{
	if (! ReleaseMutex(m_mutex))
		return MUTEX_ERROR_CANT_RELEASE_MUTEX;
	return 0;
}

Mutex::~Mutex()
{
	CloseHandle(m_mutex);
}

#endif