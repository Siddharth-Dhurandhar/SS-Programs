/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program, call fork and print the parent and child process id.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(){
	if(fork() != 0){
		pid_t pid1 = getpid();
		printf("parent process id : %d\n", pid1);
	} 
	else{
		pid_t pid2 = getpid();
		printf("child process id : %d\n", pid2);
	}
	return 0;
}
