#ifndef TRANS_STRUCT
#define TRANS_STRUCT

struct trans{
    int transID;
    int payerID; 
    int payeeID;
    int type; // -1 = withdraw, 0 = transfer, 1 = deposit
    float amt;
};

#endif