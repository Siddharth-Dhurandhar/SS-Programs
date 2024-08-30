/*
============================================================================
Name : 8.c
Author : Siddharth Dhurandhar
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>

int main(int argc, char *argv[]){
	int fd = open(argv[1], O_RDONLY);
	
	char line[1024];
	int i=0;
	while(1){
		int c = read(fd, &line[i], 1);
		if(line[i] == '\n'){
			line[i] = '\0';
			printf("%s\n",line);
			memset(line, 0, i);
			i = 0;
		}
		else if(c == 0){
			break;
		}
		else{
			i++;
		}
	}

	close(fd);

	return 0;
}
