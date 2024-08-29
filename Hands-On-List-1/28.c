/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to get maximum and minimum real time priority.
============================================================================
*/

#include<stdio.h>
#include<sched.h>

int main(){
	int max_fifo, min_fifo, max_rr, min_rr, max_other, min_other;

	max_fifo = sched_get_priority_max(SCHED_FIFO);
	min_fifo = sched_get_priority_min(SCHED_FIFO);

	max_rr = sched_get_priority_max(SCHED_RR);
	min_rr = sched_get_priority_min(SCHED_RR);

	max_other = sched_get_priority_max(SCHED_OTHER);
	min_other = sched_get_priority_min(SCHED_OTHER);

	printf("maximum priority FIFO : %d\n",max_fifo);
	printf("minimum priority FIFO : %d\n",min_fifo);

	printf("maximum priority RR : %d\n",max_rr);
	printf("minimum priority RR : %d\n",min_rr);

	printf("maximum priority OTHER : %d\n",max_other);
	printf("minimum priority OTHER : %d\n",min_other);

	return 0;
}
