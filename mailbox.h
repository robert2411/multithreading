/**************************************************************************************\
									Mailbox.h

Author		:	R.J.H.M.	Stevens
Begin		:	11-07-2014
				
Version		:	1.0.0

TODO		:	

Description	:	This is a basic Mailbox class that supports multiple platforms
				This is a template class

Dependencies:	mutex.h

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

	/**
	 *	Gives back the last message run IsEmpty() first!
	 *
	 *	@return the last message 
	 *	@warning if there is no massage in the buffer it returns random vallues
	 */
	T GetMessage();
protected:
	std::vector<T> m_mailBox;	/**< We use a vector to store the messages */
	int m_maxSize;				/**< The maximum size of the mailbox */
	Mutex mutex;				/**< The mutex to make it threadsafe */
	/**
	 *	Checks if the mailbox is empty
	 *
	 *	@warning this function is only meant for use when the mutex is already locked
	 *
	 *	@return true if empty else false
	 */
	bool IsEmptyNM();

	/**
	 *	Checks if the mailbox is full
	 *
	 *
	 *	@warning this function is only meant for use when the mutex is already locked
	 *
	 *	@return true if full else false
	 */
	bool IsFullNM();

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
	if (IsFullNM())
		return MAILBOX_ERROR_BOX_FULL;
	m_mailBox.push_back(message);
	mutex.Unlock();
	return 0;
}
template <class T>
bool Mailbox<T>::IsEmpty()
{
	mutex.Lock();
	bool out = IsEmptyNM();
	mutex.Unlock();
	return out;
}
template <class T>
bool Mailbox<T>::IsEmptyNM()
{
	if (m_mailBox.size() == 0)
		return true;
	return false;
}

template <class T>
bool Mailbox<T>::IsFull()
{
	mutex.Lock();
	bool out = IsFullNM();
	mutex.Unlock();
	return out;
}
template <class T>
bool Mailbox<T>::IsFullNM()
{
	if(m_mailBox.size() >= m_maxSize && m_maxSize != 0)
	{
		return true;
	}
	return false;
}

template <class T>
T Mailbox<T>::GetMessage()
{
	T out;
	mutex.Lock();
	if (!IsEmptyNM())
	{
		out = m_mailBox.front();
		m_mailBox.erase( m_mailBox.begin());
	}
	mutex.Unlock();
	return out;

}
#endif