#this will command all the files
NAME = threadingTest
CC = g++
all:
	$(CC) -pthread  test.cpp mutex_linux.cpp thread_general.cpp thread_linux.cpp -o $(NAME)
clean:
	rm -rf $(NAME)
