#this will command all the files
all:
	g++ -pthread  test.cpp mutex_linux.cpp thread_general.cpp thread_linux.cpp -o threadingTest

