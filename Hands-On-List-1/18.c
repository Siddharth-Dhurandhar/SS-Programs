/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to perform Record locking.
 a. Implement write lock
 b. Implement read lock
Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>

struct s {
	int train_num;
	int ticket_count;
};

int main(){
	int fd = open("ticket.txt", O_WRONLY);
	struct s r1 = {1,0};
	struct s r2 = {2,0};
	struct s r3 = {3,0};

	write(fd, &r1, sizeof(r1));
	write(fd, &r2, sizeof(r2));
	write(fd, &r3, sizeof(r3));

	close(fd);
	return 0;
}
