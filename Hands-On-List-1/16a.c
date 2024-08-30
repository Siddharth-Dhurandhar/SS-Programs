/*
============================================================================
Name : 16a.c
Author : Siddharth Dhurandhar
Description : Write a program to perform mandatory locking.
 a. Implement write lock
 b. Implement read lock
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int fd = open(argv[1], O_WRONLY);

	struct flock lock = {F_WRLCK, 0, 0, 0, 0};
	fcntl(fd, F_SETLKW, &lock);

	printf("file locked successfully.\npress any key to unlock.\n");
	getchar();

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLKW, &lock);
	printf("file unlocked.\n");

	close(fd);
	return 0;
}
