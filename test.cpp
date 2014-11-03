#include "thread.h"
#include "mutex.h"
#include "mailbox.h"
#include <stdio.h>
#include <unistd.h>
	
int test(void* test)
{
	printf("thread started - thread \r\n");
	Mailbox<int>* box = (Mailbox<int>*) test;
	//Mutex* mutex = (Mutex*) test;
	//mutex->Lock();
	//mutex->Unlock();
	while(box->IsEmpty());
	
	printf("test %d\r\n", box->GetMessage());
	sleep (100);
	return 0;
}
int main()
{
	printf("threading test program \r\n");
	Mailbox<int> box;
	//Mutex mutex;
	Thread thread;
	thread.SetThreadFunction(&test);
	thread.SetParam(&box);
	//mutex.Lock();
	thread.Start();
	printf("thread started - main  \r\n");
	box.PutMessage(1000);
	printf("message send \r\n");
	sleep(1000);
	printf("sleep \r\n");
	//mutex.Unlock();
	sleep(1000);
	printf("kill threads \r\n");
	thread.Stop();
	printf("finished \r\n");

	return 0;
}