#include "../../thread.h"
#include "../../mutex.h"
#include "../../mailbox.h"
#include <stdio.h>
int test(void* test)
{
	Mutex* mutex = (Mutex*) test;
	mutex->Lock();
	mutex->Unlock();
	printf("test\r\n");
	Sleep (100);
	return 0;
}
int main()
{
	Mailbox<int> box;
	Mutex mutex;
	Thread thread;
	thread.SetThreadFunction(&test);
	thread.SetParam(&mutex);
	mutex.Lock();
	thread.Start();
	Sleep(1000);
	mutex.Unlock();
	Sleep(1000);
	thread.Stop();

	return 0;
}