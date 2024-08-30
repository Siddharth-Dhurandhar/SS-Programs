/*
============================================================================
Name : 10.c
Author : Siddharth Dhurandhar
Description : Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
 a. check the return value of lseek
 b. open the file with od and check the empty spaces in between the data. 
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
	int fd = open(argv[1], O_RDWR | O_CREAT, S_IRWXU);

	char content[10] = "ABCDEFGHIJ";

	write(fd, &content, 10);
	int val = lseek(fd, 10, SEEK_CUR);
	write(fd, &content, 10);

	printf("return value of lseek : %d\n",val);
	
	// use od -c filename.txt to check the contents of file characterwise
	return 0;
}
