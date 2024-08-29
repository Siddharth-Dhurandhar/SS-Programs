/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to create three child processes. The parent should wait for a particular child (use waitpid system call).
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int pid1, pid2, pid3;
	int status;

	pid1 = fork();
	if(pid1 == 0){
		printf("inside child process\n");
	}

	pid2 = fork();
	if(pid2 == 0){
		sleep(20);
		printf("inside child process\n");
	}
	
	waitpid(pid2, &status, 0);

	if(WIFEXITED(status) && pid1 != 0 && pid2 != 0){
		printf("parent process runs after child process 2\n");	
	}

	return 0;
}
