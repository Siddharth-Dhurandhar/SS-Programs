/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to execute ls -Rl by the following system calls.
a. execl
b. execlp
c. execle
d. execv
e. execvp
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(){
	char *path = "/bin/ls";
	char *argv[] = {"ls", "-Rl", NULL};

	execv(path, argv);
	return 0;
}
