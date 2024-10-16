#ifndef ACCOUNT_FUNC
#define ACCOUNT_FUNC

bool addUser(struct account record, int sd){
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/account.data", O_RDWR, 0744);
    struct account endUser;
    int flag = 0;
    if(fd == -1 && errno == ENOENT){
        fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/account.data", O_RDWR | O_CREAT | O_APPEND, 0744);
        record.userID = 0;
        record.account_no = 10000;
        flag = 1;
    }

    bool result;

    int fl1;
    char wrBuff[1000];
    bzero(wrBuff, sizeof(wrBuff));
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = (-1)*sizeof(struct account);
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (-1)*sizeof(struct account), SEEK_END);
    read(fd, &endUser, sizeof(struct account));

    if(flag == 0){
        record.userID = endUser.userID + 1;
        record.account_no = endUser.account_no + 1;
    }

    printf("User ID = %d\n", record.userID);
    sprintf(wrBuff, "%s%d\n", "User ID of your new account is ", record.userID);
    record.status = 1;

    int j = write(fd, &record, sizeof(struct account));
    if(j != 0) result = true;
    else result = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    write(sd, wrBuff, sizeof(wrBuff));
    return result;
}

bool modifyUser(int userID, int newType){
    int i = userID;
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/account.data", O_RDWR, 0744);
    bool result = false;

    int fl1;
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i)*sizeof(struct account);
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    struct account currUser;
    lseek(fd, (i)*sizeof(struct account), SEEK_SET);
    read(fd, &currUser, sizeof(struct account));

    currUser.accType = newType;
    if(currUser.status == 1){
        lseek(fd, (-1)*sizeof(struct account), SEEK_CUR);
        int j = write(fd, &currUser, sizeof(struct account));
        if(j!=0) result = true;
        else result = false;
    }

    lock.l_type=F_UNLCK;
    fcntl(fd,F_SETLK,&lock);

    close(fd);
    return result;
}

struct account getUser(int ID){
    int i = ID;
    struct account currUser;
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/account.data", O_RDONLY, 0744);

    int fl1;
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i)*sizeof(struct account);
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (i)*sizeof(struct account), SEEK_SET);
    read(fd, &currUser, sizeof(struct account));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return currUser;
}

bool alterPassword(int ID, char newPwd[10], char oldPwd[10]){
	int i = ID;
	int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/account.data", O_RDWR, 0744);
	bool result;
	int fl1;

	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (i)*sizeof(struct account);
	lock.l_len = sizeof(struct account);
	lock.l_pid = getpid();

	fl1 = fcntl(fd, F_SETLKW, &lock);

	struct account currUser;
	lseek(fd, (i)*sizeof(struct account), SEEK_SET);
	read(fd, &currUser, sizeof(struct account));

	if(currUser.status == 1 && strcmp(currUser.password, oldPwd) == 0){
		strcpy(currUser.password, newPwd);
		lseek(fd, sizeof(struct account)*(-1), SEEK_CUR);
		write(fd, &currUser, sizeof(struct account));
		result = true;
	}
	else result = false;
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);
	return result;
}

bool modifyStatus(int userID, int newStatus){
    int i = userID;
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/account.data", O_RDWR, 0744);
    bool result = false;

    int fl1;
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i)*sizeof(struct account);
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    struct account currUser;
    lseek(fd, (i)*sizeof(struct account), SEEK_SET);
    read(fd, &currUser, sizeof(struct account));

    currUser.status = newStatus;
    
    lseek(fd, (-1)*sizeof(struct account), SEEK_CUR);
    int j = write(fd, &currUser, sizeof(struct account));
    if(j!=0) result = true;
    else result = false;

    lock.l_type=F_UNLCK;
    fcntl(fd,F_SETLK,&lock);

    close(fd);
    return result;
}

bool modifyCust(struct account modUser){
    int i = modUser.userID;
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/account.data", O_RDWR, 0744);
    bool result = false;

    int fl1;
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i)*sizeof(struct account);
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    struct account currUser;
    lseek(fd, (i)*sizeof(struct account), SEEK_SET);
    read(fd, &currUser, sizeof(struct account));

    strcpy(currUser.name,modUser.name);
    strcpy(currUser.password, modUser.password);

    if((currUser.status == 1) && (currUser.accType == 2)){
        lseek(fd,(-1)*sizeof(struct account),SEEK_CUR);
        int j=write(fd,&currUser,sizeof(struct account));
        if(j!=0) result=true;
        else result=false;
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}

float getBalance(int ID){
    int i = ID;
    float result;
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/account.data", O_RDONLY, 0744);
    struct account temp;

    int fl1;
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i)*sizeof(struct account);
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (i)*sizeof(struct account), SEEK_SET);
    read(fd, &temp, sizeof(struct account));

    if(temp.status == 1) result = temp.balance;
    else result = 0;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}

void writeTransaction(struct trans record){
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/transaction.data", O_RDWR);
    int flag = 0;
    struct trans endTrans;
    if(fd == -1){
        fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/transaction.data",O_RDWR | O_CREAT | O_APPEND, 0744);
        record.transID = 0;
        flag = 1;
    }

    int fl1;
    
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = (-1)*sizeof(struct trans);
    lock.l_len = sizeof(struct trans);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (-1)*sizeof(struct trans), SEEK_END);
    read(fd, &endTrans, sizeof(struct trans));

    if(flag == 0){
        record.transID = endTrans.transID + 1;
    }

    int j = write(fd, &record, sizeof(struct trans));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return;
}

bool depositMoney(int ID, float amt){
    int i = ID;
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/account.data", O_RDWR, 0744);
    bool result;

    int fl1;
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i)*sizeof(struct account);
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    struct account currUser;
    lseek(fd, (i)*sizeof(struct account), SEEK_SET);
    read(fd, &currUser, sizeof(struct account));

    if(currUser.status == 1){
        currUser.balance += amt;
        lseek(fd,(-1)*sizeof(struct account), SEEK_CUR);
        write(fd, &currUser, sizeof(struct account));
        result = true;
    }
    else result = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    // if result == true write the transaction
    if(result == true){
        struct trans temp;
        temp.payerID = currUser.userID;
        temp.payeeID = currUser.userID;
        temp.amt = amt;
        temp.type = 1;
        writeTransaction(temp);
    }

    return result;
}

bool withdrawMoney(int ID, float amt){
    int i = ID;
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/account.data", O_RDWR, 0744);
    bool result;
    int fl1;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i)*sizeof(struct account);
    lock.l_len = sizeof(struct account);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    struct account currUser;
    lseek(fd, (i)*sizeof(struct account), SEEK_SET);
    read(fd, &currUser, sizeof(struct account));

    if(currUser.status == 1 && currUser.balance >= amt){
        currUser.balance -= amt;
        lseek(fd, (-1)*sizeof(struct account), SEEK_CUR);
        write(fd, &currUser, sizeof(struct account));
        result = true;
    }
    else result = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);

    if(result == true){
        struct trans temp;
        temp.payerID = currUser.userID;
        temp.payeeID = currUser.userID;
        temp.amt = amt;
        temp.type = -1;
        writeTransaction(temp);
    }

    return result;
}

bool transferMoney(int payerID, int payeeID, float amt){
    int i1 = payerID, i2 = payeeID;
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/account.data", O_RDWR, 0744);
    bool result = false;

    int fl1, fl2;
    struct flock lock1, lock2;
    lock1.l_type = F_WRLCK;
    lock1.l_whence = SEEK_SET;
    lock1.l_start = (i1)*sizeof(struct account);
    lock1.l_len = sizeof(struct account);
    lock1.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock1);

    lock2.l_type = F_WRLCK;
    lock2.l_whence = SEEK_SET;
    lock2.l_start = (i2)*sizeof(struct account);
    lock2.l_len = sizeof(struct account);
    lock2.l_pid = getpid();

    fl2 = fcntl(fd, F_SETLKW, &lock2);

    struct account payer, payee;
    lseek(fd, (i1)*sizeof(struct account), SEEK_SET);
    read(fd, &payer, sizeof(struct account));

    lseek(fd, (i2)*sizeof(struct account), SEEK_SET);
    read(fd, &payee, sizeof(struct account));

    if(payer.status == 1 && payer.balance >= amt && payee.status == 1){
        payer.balance -= amt;
        payee.balance += amt;
        lseek(fd, (i1)*sizeof(struct account), SEEK_SET);
        write(fd, &payer, sizeof(struct account));

        lseek(fd, (i2)*sizeof(struct account), SEEK_SET);
        write(fd, &payee, sizeof(struct account));
        result = true;
    }
    else result = false;

    lock1.l_type=F_UNLCK;
    fcntl(fd,F_SETLK,&lock1);

    lock2.l_type=F_UNLCK;
    fcntl(fd,F_SETLK,&lock2);

    close(fd);

    if(result == true){
        struct trans temp;
        temp.payerID = payerID;
        temp.payeeID = payeeID;
        temp.amt = amt;
        temp.type = 0;
        writeTransaction(temp);
    }
    return result;
}


int numTransactions(int ID){
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/transaction.data", O_RDONLY);
    struct trans currTrans;
    int fl1, num = 0;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // length = 0 mtlb puri file locked
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);
    lseek(fd,0,SEEK_SET);

    while(read(fd, &currTrans, sizeof(struct trans)) == sizeof(struct trans)){
        if(currTrans.payerID == ID){
            num++;
        }
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return num;
}

void viewTransactions(int sd, int ID){
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/transaction.data", O_RDONLY);
    struct trans currTrans;
    int fl1;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // length = 0 mtlb puri file locked
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);
    lseek(fd,0,SEEK_SET);

    while(read(fd, &currTrans, sizeof(struct trans)) == sizeof(struct trans)){
        if(currTrans.payerID == ID){
            write(sd, &currTrans, sizeof(struct trans));
        }
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
}


// feedback ke liye bhi structure use karna padega lagta hai
bool writeFeedback(int sd, struct feedback record){
    bool result;

    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/feedback.txt", O_RDWR | O_APPEND);
    int flag = 0;
    if(fd == -1){
        fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/feedback.txt",O_RDWR | O_CREAT | O_APPEND, 0744);
        flag = 1;
    }

    struct flock lock;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    int fl1 = fcntl(fd, F_SETLKW, &lock);

    int j = write(fd, &record, sizeof(struct feedback));

    if(j!=0) result = true;
    else result = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}

int numFeedback(){
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/feedback.txt", O_RDONLY);
    struct feedback record;
    int fl1, num = 0;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // length = 0 mtlb puri file locked
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);
    lseek(fd,0,SEEK_SET);

    while(read(fd, &record, sizeof(struct feedback)) == sizeof(struct feedback)){
        num++;
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return num;
}

void readFeedback(int sd){
    struct feedback record;

    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/feedback.txt", O_RDONLY);

    struct flock lock;

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    int fl1 = fcntl(fd, F_SETLKW, &lock);
    lseek(fd,0,SEEK_SET);

    while(read(fd, &record, sizeof(struct feedback)) == sizeof(struct feedback)){
        write(sd, &record, sizeof(struct feedback));
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return;
}

#endif