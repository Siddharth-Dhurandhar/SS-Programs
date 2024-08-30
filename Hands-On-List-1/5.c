/*
============================================================================
Name : 5.c
Author : Siddharth Dhurandhar
Description : Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
	int fd1 = creat(argv[1], S_IRWXU);
	int fd2 = creat(argv[2], S_IRWXU);
	int fd3 = creat(argv[3], S_IRWXU);
	int fd4 = creat(argv[4], S_IRWXU);
	int fd5 = creat(argv[5], S_IRWXU);

	printf("The file descriptors are : %d, %d, %d, %d, %d\n",fd1,fd2,fd3,fd4,fd5);

	while(1);

	return 0;
}
