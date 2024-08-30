/*
============================================================================
Name : 14.c
Author : Siddharth Dhurandhar
Description : Write a program to find the type of a file.
 a. Input should be taken from command line.
 b. program should be able to identify any type of a file.
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
	struct stat s;
	printf("the file is a : ");
	int val = lstat(argv[1], &s);
	
	switch(s.st_mode & S_IFMT){
		case S_IFREG:
			printf("regular file.\n");
			break;

		case S_IFDIR:
			printf("directory.\n");
			break;

		case S_IFLNK:
			printf("symbolic link.\n");
			break;

		case S_IFCHR:
			printf("character device.\n");
			break;

		case S_IFBLK:
			printf("block device.\n");
			break;

		case S_IFIFO:
			printf("fifo.\n");
			break;

		case S_IFSOCK:
			printf("socket.\n");
			break;
		
		default:
			printf("unknown.\n");
	}
	return 0;
}
