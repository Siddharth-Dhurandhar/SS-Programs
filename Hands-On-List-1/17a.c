/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to simulate online ticket reservation. Implement write lock Write a program to open a file, store a ticket number and exit. Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h> // for memset()

int main(){
	write(1, "Enter ticket number: ", 22);
	int fd = open("ticket.txt", O_WRONLY);
	
	char buf[32];
	memset(buf, 0, 32);
	int n = read(0, &buf, 32);

	write(fd, &buf, n);
	printf("ticket number written successfully.\n");
	
	close(fd);
	return 0;
}
