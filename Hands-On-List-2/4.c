/*
============================================================================
Name : 4.c
Author : Siddharth Dhurandhar
Description : Write a program to measure how much time is taken to execute 100 getppid() system call. Use time stamp counter.
Date:  20th Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

// using time stamp counter
unsigned long long rdtsc()
{
    unsigned long long dst;
    __asm__ __volatile__("rdtsc"
                         : "=A"(dst));
    return dst;
}

void main()
{
    long long int start, end;

    start = rdtsc();
    int iter = 1;
    while (iter <= 100)
    {
        getppid();
        iter += 1;
    }

    end = rdtsc();

    printf("time required : %llu\n", end - start);
}
