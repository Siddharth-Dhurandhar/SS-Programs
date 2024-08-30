/*
============================================================================
Name : 12.c
Author : Siddharth Dhurandhar
Description : Write a program to find out the opening mode of a file. Use fcntl.
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
	int fd = open(argv[1], O_RDWR);

	int flags = fcntl(fd, F_GETFL); // find out flags
	printf("flags : %d\n",flags);

	int accessMode = flags & O_ACCMODE; // find out access mode 
	printf("access mode : %d\n",accessMode);

	if(accessMode == O_RDWR){
		printf("read write mode (O_RDWR)\n");
	}
	else if(accessMode == O_RDONLY){
		printf("read only mode (O_RDONLY)\n");
	}
	else{
		printf("write only mode (O_WRONLY)\n)");
	}

	close(fd);

	return 0;
}
