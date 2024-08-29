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
#include<sys/stat.h>

int main(){
	const char *src = "/home/siddharth-dhurandhar/myscripts/ss_programs/myfifo";

	int val = mkfifo(src, S_IRWXU);

	if(val == 0){
		printf("FIFO file is created successfully\n");
	}

	return 0;
}

