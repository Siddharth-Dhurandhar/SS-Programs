/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to simulate online ticket reservation. Implement write lock Write a program to open a file, store a ticket number and exit. Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>

int main(){
	int fd = open("ticket.txt", O_RDWR);
	struct flock lock = {F_WRLCK, 0, 0, 0, 0};
	fcntl(fd, F_SETLKW, &lock);
	write(1, "file is locked.\n", 17);
	
	char buf[32];
	int n = read(fd, &buf, 32);
	
	int val = atoi(buf); // convert char to int and return value
	val++;
	
	sprintf(buf, "%d", val); // convert int to char and write to buf
	
	lseek(fd, 0, SEEK_SET);
	write(fd, &buf, strlen(buf));

	printf("the ticket number is : %d\n", val);
	getchar();

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLKW, &lock);
	printf("file is unlocked.\n");
	close(fd);
	return 0;
}
