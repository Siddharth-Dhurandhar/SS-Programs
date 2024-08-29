/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO, SCHED_RR).
============================================================================
*/

#include<stdio.h>
#include<sched.h>
#include<unistd.h>

// ROOT ACCESS IS NEEDED FOR USING sched_setscheduler(). LOGIN AS ROOT USING sudo -s .

int main(){
	int pid = getpid();

	int sched_policy = sched_getscheduler(pid);

	switch(sched_policy) {
		case SCHED_FIFO :
			printf("scheduling policy used : FIFO\n");
			break;
		case SCHED_RR :
			printf("scheduling policy used : RR\n");
			break;
		case SCHED_OTHER :
			printf("scheduling policy used : OTHER\n");
			break;
		default :
			break;
	}

	int input;
	printf("select the new scheduling policy :\n1. FIFO\n2. RR\n3. OTHER\n");
	scanf("%d",&input);

	struct sched_param s;
	
	switch(input){
		case 1 :
			s.sched_priority = 99;
			sched_setscheduler(pid, SCHED_FIFO, &s);
			break;
		case 2 :
			s.sched_priority = 99;
			sched_setscheduler(pid, SCHED_RR, &s);
			break;
		case 3 :
			s.sched_priority = 0;
			sched_setscheduler(pid, SCHED_OTHER, &s);
			break;
		default :
			printf("invalid\n");
			break;
	}

	printf("\n");
	

	// check the new scheduling policy assigned
	
	sched_policy = sched_getscheduler(pid);

        switch(sched_policy) {
                case SCHED_FIFO :
                        printf("new scheduling policy : FIFO\n");
                        break;
                case SCHED_RR :
                        printf("new scheduling policy : RR\n");
                        break;
                case SCHED_OTHER :
                        printf("new scheduling policy : OTHER\n");
                        break;
                default :
                        break;
        }

	return 0;
}
