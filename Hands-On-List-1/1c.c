/*
============================================================================
Name : 1c.c
Author : Siddharth Dhurandhar
Description : Create the following types of a files using (i) shell command (ii) system call
		 a. soft link (symlink system call)
		 b. hard link (link system call)
		 c. FIFO (mkfifo Library Function or mknod system call)
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>

int main(){
	const char *src = "/home/siddharth-dhurandhar/myscripts/ss_programs/myfifo";

	int val = mkfifo(src, S_IRWXU);

	if(val == 0){
		printf("FIFO file is created successfully\n");
	}

	return 0;
}

