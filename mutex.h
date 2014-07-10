/**************************************************************************************\
									mutex.h

Author		:	R.J.H.M.	Stevens
Begin		:	10-07-2014
				
Version		:	1.0.0

Description	:	This is a basic mutex class that supports multiple platforms

Changes		:
				10-07-2014	-	Setting up the basic structor of the class		

\**************************************************************************************/

#ifndef MUTEX_H_
#define MUTEX_H_

#include <windows.h>
#include "mutex_errors.h"

template <class T>
class Mutex
{
protected:
	T m_variable;
	int m_lastError;
	HANDLE m_mutex;

public:
	Mutex()
	{
		m_lastError = 0;
		m_mutex = CreateMutex( 
			NULL,              // default security attributes
			FALSE,             // initially not owned
			NULL);             // unnamed mutex
	};	
	~Mutex()
	{
	};
	int Lock()
	{
		DWORD dwWaitResult;
		dwWaitResult = WaitForSingleObject( 
				m_mutex,    // handle to mutex
				INFINITE);  // no time-out interval

		if (dwWaitResult == WAIT_OBJECT_0 )
			return 0;

		if (dwWaitResult == WAIT_ABANDONED)
		{
			m_lastError = MUTEX_ERROR_LOCK_WAIT_ABANDONED;
			return MUTEX_ERROR_LOCK_WAIT_ABANDONED;
		}

		m_lastError = MUTEX_ERROR_LOCK_ERROR;
		return MUTEX_ERROR_LOCK_ERROR;

	};
	int Unlock()
	{
		if (! ReleaseMutex(m_mutex))
		{
			m_lastError = MUTEX_ERROR_CANT_RELEASE_MUTEX;
			return MUTEX_ERROR_CANT_RELEASE_MUTEX;
		}
		return 0;
	};
	
	T GetVar()
	{
		return m_variable;
	};

	int SetVar(T variable)
	{
		m_variable = variable;
		return 0;
	};
	T* GetVarPointer()
	{
			return &m_variable;
	};
};

#endif