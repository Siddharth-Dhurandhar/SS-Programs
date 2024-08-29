/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to perform mandatory locking.
 a. Implement write lock
 b. Implement read lock
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int fd = open(argv[1], O_RDONLY);

	struct flock lock = {F_RDLCK, 0, 0, 0, 0};
	fcntl(fd, F_SETLK, &lock);

	printf("file locked successfully.\nmultiple readers can enter\n");
	printf("writers are not allowed.\n");
	getchar();

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLKW, &lock);

	printf("file unlocked.\n");
	close(fd);

	return 0;
}
