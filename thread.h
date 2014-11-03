/**************************************************************************************\
									Thread.h

Author		:	R.J.H.M.	Stevens
Begin		:	10-07-2014
				
Version		:	1.1.0

Description	:	This is a basic threading class that supports multiple platforms

Todo		:	Add a pause/resurm function  - add the thread id function - write the linux port

Changes		:
				03-11-2014	-	Added linux support
				10-07-2014	-	Adding comments
				10-07-2014	-	Setting up the basic structure of the class		

\**************************************************************************************/
#ifndef THREAD_H_
#define THREAD_H_

/*
 *	Windows specific includes
 */
#ifdef _WIN32
#include <windows.h>
#endif

/*
 *	Linux specific includes
 */
#ifdef __linux__
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#endif
/*
 *	General includes
 */
#include "thread_errors.h"

class Thread
{
public:
	Thread();
	/**
	 *	Set the function that has to run and tell if it has to run in a while (true) loop
	 *
	 *	@param p_function the pointer to the function that has to run as a thread format (int FunctionName (void*))
	 *
	 *	@return 0 on success else >0
	 */
	int SetThreadFunction(int (*p_function)(void*));
	
	/**
	 *	Set the parameters that have to be send to the thread
	 *
	 *	@return 0 on success else >07-2014
	 */
	int SetParam(void* p_param);
	
	/**
	 *	Start the thread
	 *	
	 *	@return 0 on success else >0
	 */
	int Start();
	
	/**
	 *	Stop the thread
	 *
	 *	@return 0 on success else >0
	 */
	int Stop();

	/**
	 *	@warning this function is not implemented
	 *	@return The thread ID
	 */
	int GetThreadId();

	~Thread();

protected:
	/*
	 *	Windows specific threading functions
	 */
	#ifdef _WIN32
	/**
	 *	This function calls the function that is stored in the function pointer
	 */
	static DWORD WINAPI ThreadRunner(LPVOID lpParam);
	#endif

	void* mp_param;				/**< A pointer to the param that has to be send to the thread */
	int (*mp_function)(void*);	/**< A pointer to the function that has to run as a thread */

	#ifdef _WIN32
	HANDLE m_thread;			/**< (WINDOWS) a handle that holds the thread */
	DWORD m_threadId;			/**< (WINDOWS) the thread ID */
	#endif
	
	#ifdef __linux__
	pthread_t m_thread;			/**< (LINUX) The thread is strored in here.  */
	static void* ThreadRunner(void* ptr);
	int m_threadId;
	#endif	
};

#endif

//#if __cplusplus > 199711L