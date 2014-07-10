#include "../../thread.h"
#include "../../mutex.h"
#include <stdio.h>
int test(void* test)
{
	Mutex<int>* mutex = (Mutex<int>*) test;
	int var = mutex->GetVar();
	printf("test %d\r\n", var);
	Sleep (100);
	return 0;
}
int main()
{
	Mutex<int> mutex;
	Thread thread;
	thread.SetThreadFunction(&test);
	thread.SetParam(&mutex);
	mutex.Lock();
	mutex.SetVar(100);
	thread.Start();
	Sleep(1000);
	mutex.Unlock();
	Sleep(1000);
	thread.Stop();

	return 0;
}