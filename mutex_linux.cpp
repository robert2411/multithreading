#ifdef __linux__
#include "mutex.h"

Mutex::Mutex()
{
	m_mutex = PTHREAD_MUTEX_INITIALIZER;
	//pthread_mutex_init(&m_mutex, NULL);
}

int Mutex::Lock()
{
	pthread_mutex_lock(&m_mutex);
	return 0;
}

int Mutex::Unlock()
{
	pthread_mutex_unlock(&m_mutex);
	return 0;
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&m_mutex);
}

#endif