/*
============================================================================
Name : 23.c
Author : Siddharth Dhurandhar
Description : Write a program to create a Zombie state of the running program.
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(){
	int fd = fork();

	if(fd == 0){
		printf("child process id : %d\n",getpid());
	}
	else{
		sleep(60);
		printf("parent process id : %d\n",getpid());
	}

	// To check the state of child process open another terminal and use
	// "ps aux | grep 23.out" or check the PID of child process in htop
	return 0;
}
