#ifndef ACCOUNT_STRUCT
#define ACCOUNT_STRUCT

struct account{
    int accType; // 0 - manager, 1 - employee, 2 - customer
    int userID;
    char name[30];
    char password[10];
    int account_no;
    float balance;
    int status;
};

#endif