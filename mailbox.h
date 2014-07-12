/**************************************************************************************\
									Mailbox.h

Author		:	R.J.H.M.	Stevens
Begin		:	10-07-2014
				
Version		:	1.0.0

TODO		:	Inplement the linux support
Description	:	This is a basic Mailbox class that supports multiple platforms

Changes		:
				12-07-2014	-	Adding comments
				11-07-2014	-	Setting up the basic structor of the class		

\**************************************************************************************/
#ifndef MAILBOX_H_
#define MAILBOX_H_
#include <vector>
#include "mutex.h"
#include "mailbox_errors.h"

template <class T>
class Mailbox
{
public:
	/**
	*	Create the mailbox with no size limet
	*/
	Mailbox();

	/**
	 *	@param size The maximum size of the mailbox 0 for an unlimmeted size
	 */
	Mailbox(int size);

	/**
	 *	Set the size of the mailbox
	 *	
	 *	@param size the maximum size of the mailbox
	 *
	 *	@return 0 on success else >0
	 */
	int SetSize(int size);

	/**
	 *	Add a message to the mailbox its smart to run IsFull() first
	 *
	 *	@param message the message that has to be mailt to the other thread
	 *
	 *	@return 0 on success else >0
	 */
	int PutMessage(T message);

	/**
	 *	Checks if the mailbox is empty
	 *
	 *	@return true if empty else false
	 */
	bool IsEmpty();

	/**
	 *	Checks if the mailbox is full
	 *
	 *	@return true if full else false
	 */
	bool IsFull();
	T GetMessage();
protected:
	std::vector<T> m_mailBox;
	int m_maxSize;
	Mutex mutex;
};

template <class T>
Mailbox<T>::Mailbox()
{
	m_maxSize = 0;
}

template <class T>
Mailbox<T>::Mailbox(int size)
{
	m_maxSize = size;
}

template <class T>
int Mailbox<T>::SetSize(int size)
{
	m_maxSize = size;
	return 0;
}

template <class T>
int Mailbox<T>::PutMessage(T message)
{
	mutex.Lock();
	if (IsFull())
		return MAILBOX_ERROR_BOX_FULL;
	m_mailBox.push_back(message);
	mutex.Unlock();
	return 0;
}
template <class T>
bool Mailbox<T>::IsEmpty()
{
	mutex.Lock();
	if (m_mailBox.size() == 0)
		return true;
	mutex.Unlock();
	return false;
}

template <class T>
bool Mailbox<T>::IsFull()
{
	mutex.Lock();
	if(m_mailBox.size() >= m_maxSize && m_maxSize != 0)
	{
		mutex.Unlock();
		return true;
	}
	mutex.Unlock();
	return false;
}

template <class T>
T Mailbox<T>::GetMessage()
{
	T out;
	mutex.Lock();
	if (!IsEmpty())
	{
		out = m_mailBox.front();
		m_mailBox.erase( m_mailBox.begin());
	}
	mutex.Unlock();
	return out;

}
#endif