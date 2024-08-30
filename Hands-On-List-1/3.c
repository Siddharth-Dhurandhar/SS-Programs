/*
============================================================================
Name : 3.c
Author : Siddharth Dhurandhar
Description : Write a program to create a file and print the file descriptor value. Use creat ( ) system call.
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
	int fd = creat(argv[1],S_IRWXU);
	printf("file desciptor value : %d\n",fd);
	return 0;
}
