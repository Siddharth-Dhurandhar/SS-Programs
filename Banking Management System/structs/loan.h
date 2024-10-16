#ifndef LOAN_STRUCT
#define LOAN_STRUCT

struct loan {
    int loanID;
    int custID;
    int empID; // -1 = not assigned, other = assigned
    float amt;
    int granted; // -1 = pending, 0 = not granted, 1 = granted
};

#endif