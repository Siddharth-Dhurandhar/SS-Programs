/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Find out the priority of your running program. Modify the priority with nice command.
============================================================================
*/

#include<stdio.h>
#include<unistd.h> // for nice(), getpid()
#include<sys/resource.h> // for getpriority(), constants like PRIO_PROCESS

int main(){
	int priority;
	pid_t pid = getpid();
	
	priority = getpriority(PRIO_PROCESS, pid);

	printf("current priority : %d\n", priority);

	nice(5); // increase priority by 5
	
	priority = getpriority(PRIO_PROCESS, pid);

	printf("new priority : %d\n", priority);
	return 0;
}
