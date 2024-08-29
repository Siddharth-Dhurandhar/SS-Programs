/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to verify whether the data is available within 10 seconds or not (check in $man 2 select).
============================================================================
*/

#include<stdio.h>
#include<sys/select.h>
#include<time.h>

int main(){
	struct timeval t;
	t.tv_sec = 10; 
	t.tv_usec = 0;
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(0,&fd);
	
	int val = select(1, &fd, NULL, NULL, &t);
	
	if(val == 0){
		printf("data not available within timeout.\n");
	}
	else{
		printf("data is available within timeout.\n");
	}

	return 0;
}
