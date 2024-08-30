/*
============================================================================
Name : 9.c
Author : Siddharth Dhurandhar
Description : Write a program to print the following information about a given file.
 a. inode
 b. number of hard links
 c. uid
 d. gid
 e. size
 f. block size
 g. number of blocks
 h. time of last access
 i. time of last modification
 j. time of last change
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/stat.h> //used for stat structure and stat function
#include<time.h> // used to manipulate time
#include<string.h>

int main(int argc, char *argv[]){
	struct stat s;
	stat(argv[1], &s);

	printf("inode number : %ld\n",s.st_ino);
	printf("number of hard links : %ld\n",s.st_nlink);
	printf("uid : %u\n",s.st_uid);
	printf("gid : %u\n",s.st_gid);
	printf("size : %ld\n",s.st_size);
	printf("block size : %ld\n",s.st_blksize);
	printf("number of blocks : %ld\n",s.st_blocks);
	printf("time of last access : %ld\n",s.st_atime);
	printf("time of last modification : %ld\n",s.st_mtime);
	printf("time of last change : %ld\n",s.st_ctime);

	return 0;
}
