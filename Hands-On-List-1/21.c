/*
============================================================================
Name : 21.c
Author : Siddharth Dhurandhar
Description : Write a program, call fork and print the parent and child process id.
Date: 30th Aug, 2024.
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
