/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(){
	char input_buffer[50];

	// 0 is file descriptor for STDIN, which is keyboard
	// 1 if file descriptor for STDOUT, which is console
	
	int n = read(0, input_buffer, 50);
	write(1, input_buffer, n);

	return 0;
}