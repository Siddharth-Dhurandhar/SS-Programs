/*
============================================================================
Name : 11.c
Author : Siddharth Dhurandhar
Description : Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not.
 a. use dup
 b. use dup2
 c. use fcntl
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	char text1[27] = "Written using original fd.\n";
	char text2[37] = "Written using dup() file descriptor.\n";
	char text3[38] = "Written using dup2() file descriptor.\n";
	char text4[39] = "Written using fcntl() file descriptor.\n";

	int fd1 = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	write(fd1, &text1, sizeof(text1));

	int fd2 = dup(fd1);
	write(fd2, &text2, sizeof(text2)); // duplicates fd1 and assigns next smallest 
					   // fd available

	int fd3 = dup2(fd1, 10); // duplicates fd1 and assigns fd3 = 10
				 //  if it is not available then closes it and assigns it
	write(fd3, &text3, sizeof(text3));

	int fd4 = fcntl(fd1, F_DUPFD, 5); // duplicates fd1 and assigns next smallest 
					  // available fd which is greater than or 
					  // equal to 5
	write(fd4, &text4, sizeof(text4));
	
	
	close(fd1);
	return 0;
}
