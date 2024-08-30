/*
============================================================================
Name : 18a.c
Author : Siddharth Dhurandhar
Description : Write a program to perform Record locking.
 a. Implement write lock
 b. Implement read lock
Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

struct s {
	int train_num;
	int ticket_count;
};

int main() {
	int fd = open("ticket.txt", O_RDWR);
	printf("Select train number (1,2,3): \n");
	int tno;
	scanf("%d", &tno);
	getchar();

	struct s db;

	struct flock lock = {F_WRLCK, 0, (tno-1)*sizeof(db), sizeof(db), 0};

	fcntl(fd, F_SETLKW, &lock);

	lseek(fd, (tno - 1)*sizeof(db), SEEK_SET);
	read(fd,&db, sizeof(db));
	
	printf("Ticket number: %d \n", db.ticket_count);
	db.ticket_count++;
	
	lseek(fd, (tno - 1)*sizeof(db), SEEK_SET);
	write(fd, &db, sizeof(db));

	printf("To Book Ticket, press Enter: \n");
	getchar();

	lock.l_type=F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	printf("Booked\n");

	close(fd);
	return 0;
}
