/*
============================================================================
Name : 7.c
Author : Siddharth Dhurandhar
Description : Write a program to copy file1 into file2 ($cp file1 file2).
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1){
		printf("Error while opening src file.\n");
		close(fd1);
	}

	int fd2 = open(argv[2], O_WRONLY | O_CREAT, S_IRWXU);
	if(fd2 == -1){
		printf("Error while opening or creating destination file.\n");
		close(fd2);
	}

	char c;

	while(1){
		int n = read(fd1,&c,1);
		if(n == 0){
			break;
		}
		write(fd2,&c,1);
	}

	printf("Copied successfully.\n");
	close(fd1);
	close(fd2);

	return 0;
}
