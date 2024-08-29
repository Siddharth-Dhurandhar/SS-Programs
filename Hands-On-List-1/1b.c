/*
============================================================================
NAME : Siddharth Dhurandhar
ROLL NO : MT2024151

Create the following types of a files using (i) shell command (ii) system call
 a. soft link (symlink system call)
 b. hard link (link system call)
 c. FIFO (mkfifo Library Function or mknod system call)
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(){
	const char *src = "/home/siddharth-dhurandhar/myscripts/ss_programs/src2.txt";
	const char *hardlink = "/home/siddharth-dhurandhar/myscripts/ss_programs/hardlink.txt";

	int val = link(src, hardlink);

	if(val == 0){
		printf("hardlink created successfully\n");
	}

	return 0;
}

