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

struct s {
	int train_num;
	int ticket_count;
};

int main() {
	int fd = open("ticket.txt", O_RDONLY);
	printf("Select train number (1,2,3): \n");
	int tno;
	scanf("%d", &tno);
	getchar();

	struct s db;

	struct flock lock = {F_RDLCK, 0, (tno-1)*sizeof(db), sizeof(db), 0};

	fcntl(fd, F_SETLKW, &lock);

	lseek(fd, (tno - 1)*sizeof(db), SEEK_SET);
	read(fd,&db, sizeof(db));
	
	printf("Ticket number: %d \n", db.ticket_count);

	printf("To unlock, press Enter: \n");
	getchar();

	lock.l_type=F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	printf("unlocked\n");

	close(fd);
	return 0;
}

