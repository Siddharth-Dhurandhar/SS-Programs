/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to run a script at a specific time using a Daemon process.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	time_t curr, deadline;
	struct tm *t;

	time(&curr);
	t = localtime(&curr);

	t->tm_hour = atoi(argv[1]);

	if(argv[2] != NULL){
		t->tm_min = atoi(argv[2]);
	}
	else{
		t->tm_min = 0;
	}

	if(argv[3] != NULL){
		t->tm_sec = atoi(argv[3]);
	}
	else{
		t->tm_sec = 0;
	}

	deadline = mktime(t);

	int pid = fork();

	if(pid == 0){
		setsid();
		do
		{
			time(&curr);
			sleep(1);
			printf("daemon active\n");
		} while(difftime(deadline,curr) > 0);
		
		printf("process ended\n");
	}
	else{
		exit(0);
	}

	return 0;
}
