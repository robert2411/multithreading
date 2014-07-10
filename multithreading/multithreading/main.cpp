#include "../../thread.h"
#include <stdio.h>
int test(void* test)
{
	printf("test\r\n");
	Sleep (100);
	return 0;
}
int main()
{
	Thread thread;
	thread.SetThreadFunction(&test);
	thread.Start();
	Sleep(1000);
	thread.Stop();

	return 0;
}