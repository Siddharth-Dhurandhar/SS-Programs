/*
============================================================================
Name : 22.c
Author : Siddharth Dhurandhar
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file. 
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

int main(int argc, char *argv[]){
	fork();

	int fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	char buffer[50] = {0};
	
	pid_t pid = getpid();

	sprintf(buffer, "process with pid : %d\n", pid);

	write(fd, &buffer, sizeof(buffer));

	return 0;
}
