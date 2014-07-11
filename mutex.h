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

#ifdef _WIN32
#include <windows.h>
#endif

#include "mutex_errors.h"

class Mutex
{
public:
	Mutex();	
	~Mutex();
	
	/**
	 *	Lock the mutex
	 *
	 *	@return 0 on success else >0
	 */
	int Lock();
	
	/**
	 *	Lock the mutex
	 *
	 *	@return 0 on success else >0
	 */
	int Unlock();

protected:

	#ifdef _WIN32
	HANDLE m_mutex;		/**< (windows) The handler for the mutex */
	#endif
};

#endif