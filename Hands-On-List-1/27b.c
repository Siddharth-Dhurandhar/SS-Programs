/*
============================================================================
Name : 27b.c
Author : Siddharth Dhurandhar
Description : Write a program to execute ls -Rl by the following system calls.
a. execl
b. execlp
c. execle
d. execv
e. execvp
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(){
	execlp("ls", "ls", "-Rl", NULL);
	return 0;
}
