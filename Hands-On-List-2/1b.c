/*
============================================================================
Name : 1b.c
Author : Siddharth Dhurandhar
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and 10 micro second a. ITIMER_REAL b. ITIMER_VIRTUAL c. ITIMER_PROF
Date:  20th Sept, 2024.
============================================================================
*/
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void main(int argc, char const *argv[])
{
    struct itimerval timer;
    printf("Select interval timer\n1:10s\n2:10micros\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 0;
        timer.it_value.tv_sec = 10;
        timer.it_value.tv_usec = 0;
        break;
    case 2:
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 0;
        timer.it_value.tv_sec = 0;
        timer.it_value.tv_usec = 10;
        break;
    default:
        perror("INVALID CHOICE");
        _exit(1);
        break;
    }
    int timerStatus = setitimer(ITIMER_VIRTUAL, &timer, 0);
    if (timerStatus == -1)
        perror("Error while setting an interval timer!");

    while (1)
        ;
}
