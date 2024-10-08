/*
============================================================================
Name : 19.c
Author : Siddharth Dhurandhar
Description : Write a program to find out time taken to execute getpid system call. Use time stamp counter.
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

unsigned long long rdtsc(){
	unsigned long long dst;
	__asm__ __volatile__("rdtsc" : "=A"(dst));
	return dst;
}

int main(){
	unsigned long long start, end;
	int pid;
	start = rdtsc();
	pid = getpid();
	end = rdtsc();
	printf("process id : %d\n",pid);
	printf("time taken : %llu cpu cycles\n",end-start);

	return 0;
}
