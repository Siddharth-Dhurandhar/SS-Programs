/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to open an existing file with read write mode. Try O_EXCL flag also. 
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
	int fd1 = open(argv[1],O_RDWR);
	printf("file descriptor of opened file : %d\n",fd1);
	
	int fd2 = open(argv[1],O_EXCL);
	printf("file descriptor of opened file : %d\n",fd2);
	return 0;
}
