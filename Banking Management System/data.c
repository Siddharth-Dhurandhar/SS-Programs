#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

#include "./structs/admin.h"

int getNewAdmin(){
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/admin.data", O_RDONLY, 0744);
    if(fd == -1 && errno == ENOENT){
        return 0;
    }

    struct admin record;
    lseek(fd, (-1)*sizeof(struct admin), SEEK_END);
    read(fd, &record, sizeof(struct admin));
    close(fd);

    return record.userID + 1;
}

int main(){
    int choice = 0;
    struct admin newAdmin;
    newAdmin.userID = getNewAdmin();

    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/admin.data",O_RDWR | O_CREAT | O_APPEND, 0744);
    printf("Please enter the name of the admin : ");
    scanf("%s",newAdmin.username);
    printf("Please enter the password(max 10 characters) : ");
    scanf("%s",newAdmin.password);
    printf("Your useID is : %d\n",newAdmin.userID);
    write(fd, &newAdmin, sizeof(struct admin));
    
    close(fd);
    return 0;
}