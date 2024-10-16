#ifndef LOAN_FUNC
#define LOAN_FUNC

bool createEntry(struct loan record, int sd){
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/LoanData/loan.data", O_RDWR, 0744);
    struct loan endLoan;
    
    if(fd == -1 && errno == ENOENT){
        fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/LoanData/loan.data", O_RDWR | O_CREAT | O_APPEND, 0744);
        record.loanID = 0;
    }

    bool result;
    int fl1;
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = (-1)*sizeof(struct loan);
    lock.l_len = sizeof(struct loan);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    if (lseek(fd, 0, SEEK_END) == 0) {
        record.loanID = 0;
    } else {
        lseek(fd, (-1) * sizeof(struct loan), SEEK_END);
        read(fd, &endLoan, sizeof(struct loan));
        record.loanID = endLoan.loanID + 1;
    }

    record.granted = -1;
    record.empID = -1;

    printf("Loan ID = %d\n", record.loanID);
    printf("Customer ID = %d\n", record.custID);

    int j = write(fd, &record, sizeof(struct loan));
    if(j == sizeof(struct loan)) result = true;
    else result = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}

int numLoan(int custID, int empID){
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/LoanData/loan.data", O_RDONLY);
    struct loan currLoan;
    int fl1, num = 0;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // length = 0 mtlb puri file locked
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);
    lseek(fd,0,SEEK_SET);

    while(read(fd, &currLoan, sizeof(struct loan)) == sizeof(struct loan)){
        if(currLoan.custID == custID && currLoan.empID == empID){
            num++;
        }
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return num;
}

void searchLoan(int sd, int custID, int empID){
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/LoanData/loan.data", O_RDONLY);
    struct loan currLoan;
    int fl1;

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // length = 0 mtlb puri file locked
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);
    lseek(fd,0,SEEK_SET);

    while(read(fd, &currLoan, sizeof(struct loan)) == sizeof(struct loan)){
        if(currLoan.custID == custID && currLoan.empID == empID){
            write(sd, &currLoan, sizeof(struct loan));
        }
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
}

bool giveLoan(int loanID, int empID, int val){
    int i = loanID;
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/LoanData/loan.data", O_RDWR);
    struct loan currLoan;
    int fl1;
    bool result;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i)*sizeof(struct loan);
    lock.l_len = sizeof(struct loan);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (i)*sizeof(struct loan), SEEK_SET);
    read(fd, &currLoan, sizeof(struct loan));

    if(currLoan.empID == empID ){
        currLoan.granted = val;

        lseek(fd, (i)*sizeof(struct loan), SEEK_SET);
        int j = write(fd, &currLoan, sizeof(struct loan));

        if(j!=0) result = true;
        else result = false;
    }
    else result = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}

bool mapLoan(int loanID, int empID){
    int i = loanID;
    int fd = open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/LoanData/loan.data", O_RDWR);
    struct loan currLoan;
    int fl1;
    bool result;

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (i)*sizeof(struct loan);
    lock.l_len = sizeof(struct loan);
    lock.l_pid = getpid();

    fl1 = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, (i)*sizeof(struct loan), SEEK_SET);
    read(fd, &currLoan, sizeof(struct loan));

    currLoan.empID = empID;

    lseek(fd, (i)*sizeof(struct loan), SEEK_SET);
    int j = write(fd, &currLoan, sizeof(struct loan));

    if(j!=0) result = true;
    else result = false;

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    return result;
}

#endif