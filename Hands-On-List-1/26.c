/*
============================================================================
Name : 26.c
Author : Siddharth Dhurandhar
Description : Write a program to execute an executable program.
 a. use some executable program
 b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){
	int status;
	pid_t pid = fork();

	if(pid == 0){
		//char *args[] = {"./name.out", "Siddharth", NULL};

		execv(argv[1], &argv[1]);
	}
	else{
		wait(&status);

		if(WIFEXITED(status)){
			printf("child process exit status : %d\n",status);
		}
	}

	return 0;
}
