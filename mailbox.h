#ifndef MAILBOX_H_
#define MAILBOX_H_
#include <vector>

template <class T>
class Mailbox
{
public:
	Mailbox();
	Mailbox(int size);
	int SetSize(int size);
	int PutMessage(T message);
	bool IsEmpty();
	bool IsFull();
	T GetMessage();
	int GetLastError();
protected:
	std::vector<T> m_mailBox;
	int m_maxSize;
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
	if (IsFull())
		return MAILBOX_ERROR_BOX_FULL;

	m_mailBox.push_back(message);
	return 0;
}
template <class T>
bool Mailbox<T>::IsEmpty()
{
	if (m_mailBox.size == 0)
		return true;
	return false;
}

template <class T>
bool Mailbox<T>::IsFull()
{
	if(m_mailBox.size >= m_maxSize && m_maxSize != 0)
		return true;
	return false;
}

template <class T>
T Mailbox<T>::GetMessage()
{
	T out;
	if (!IsEmpty())
	{
		out = m_mailBox.front();
		m_mailBox.erase( m_mailBox.begin())
	}
	return out;

}
#endif