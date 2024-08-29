/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to create an orphan process.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(){
	int fd = fork();

	if(fd == 0){
		sleep(60);
		printf("child process id : %d\n", getpid());
		printf("parent process id : %d\n", getppid());
	}
	else{
		printf("parent process id : %d\n", getpid());
		sleep(30);
	}

	// while the child process sleeps the parent process will return 
	// so the child process will become an orphan process. we can check
	// this by looking at the return value of getppid()
	
	return 0;
}
