/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to display the environmental variable of the user (use environ).
============================================================================
*/

#include<stdio.h>

int main(){
	extern char **environ;
	char **env = environ;

	while(*env){
		printf("%s\n", *env);
		env++;
	}

	return 0;
}
