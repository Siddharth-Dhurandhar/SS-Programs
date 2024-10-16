#ifndef CLIENT_FUNC
#define CLIENT_FUNC


void attemptAdminLogin(int sd){
	bool result;
	struct admin currUser;
	printf("User ID : ");
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	printf("Password : ");
	char* pass = getpass("");
	strcpy(currUser.password, pass);

	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(struct admin));

	read(sd,&result,sizeof(result));

	if(!result){
		printf("Invalid login!\nEither your Password didn't match OR your Account is Deleted\n");
		chooseOption(sd);
	}
	else{
		printf("Succesfully logged in!\n\n");
	}
	return;
}

void addAccount(int sd){
    int select = 1, type;
    bool result;
    char rdBuff[1000];
    bzero(rdBuff, sizeof(rdBuff));
    write(sd, &select, sizeof(int));

    if(option == 1){
        printf("Enter account type\n0: Manager Account\n1: Employee Account\n2: Customer Account\n");
        scanf("%d",&type);
    }
    else{
        type = 2;
    }
    
    struct account addUser1;
    addUser1.accType = type;
    printf("Name of the account holder : ");
    scanf("%s",addUser1.name);
    printf("Password(max 10 characters) : ");
    char *pass = getpass("");
    strcpy(addUser1.password, pass);

    printf("Initial Deposit : Rs.");
    scanf("%f",&addUser1.balance);
    write(sd, &addUser1, sizeof(struct account));
    read(sd, rdBuff, sizeof(rdBuff));

    read(sd, &result, sizeof(result));

    if(!result){
        printf("Error adding the account!\n\n");
    }
    else{
        printf("Successfully added the account!\n\n");
    }

    printf("%s\n",rdBuff);
    showMenu(sd);
}

void modifyAccount(int sd){
    int select = 2, userID, type;
    bool result;

    write(sd, &select, sizeof(int));

    printf("Enter the user ID to be modified : ");
    scanf("%d", &userID);
    printf("Enter account type\n0: Manager Account\n1: Employee Account\n2: Customer Account\n");
    scanf("%d",&type);

    while(type < 0 || type > 2){
        printf("Invalid type!\n");
        printf("Enter account type\n0: Manager Account\n1: Employee Account\n2: Customer Account\n");
        scanf("%d",&type);
    }

    write(sd, &userID, sizeof(int));
    write(sd, &type, sizeof(int));

    read(sd,&result,sizeof(result));

	if(!result){
		printf("Error modifying the account ,please re-check the User ID!\n\n");
	}
	else{
		printf("Succesfully modified the account!\n\n");
	}
	showMenu(sd);
    return;
}

void viewDetails(int sd){
    int select = 3, userID;

    write(sd, &select, sizeof(int));
    printf("Enter user ID : ");
    scanf("%d",&userID);
    write(sd, &userID, sizeof(int));

    struct account currUser1;
    read(sd, &currUser1, sizeof(struct account));
    printf("\nUser ID : %d\n", currUser1.userID);
    printf("Name : %s\n",currUser1.name);
    printf("Password : %s\n",currUser1.password);
    printf("Account Number : %d\n",currUser1.account_no);
    printf("Available balance : RS.%0.2f\n",currUser1.balance);

    printf("Account type : ");
    if(currUser1.accType == 0) printf("Manager\n");
    else if(currUser1.accType == 1) printf("Employee\n");
    else printf("Customer\n");
    
    if(currUser1.status == 1) printf("Status : ACTIVE\n\n");
    else printf("Status : NOT ACTIVE\n\n");

    showMenu(sd);
    return;
}

void changePassword(int sd, int select){
    int userID;
    char oPassword[10];
    char nPassword[10];
    bool result;

    if(option == 1 || option == 2){
        printf("Enter user ID : ");
        scanf("%d",&userID);
    }
    else{
        userID = currUserID;
    }

    printf("Enter your current password : ");
    char *pass = getpass("");
    strcpy(oPassword, pass);

    write(sd, &select, sizeof(int));
    write(sd, &userID, sizeof(int));
    write(sd, oPassword, sizeof(oPassword));
    printf("Enter the new password(max 10 characters) : ");
    pass = getpass("");
    strcpy(nPassword, pass);
    write(sd, nPassword, sizeof(nPassword));

    read(sd, &result, sizeof(result));
    
    if(!result){
        printf("Error changing your password\n\n");
    }
    else{
        printf("Successfully changed your password!\n\n");
    }

    showMenu(sd);
    return;
}

void attemptOtherLogin(int sd){
    bool result;
	struct account currUser;
	printf("User ID : ");
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	printf("Password : ");
	char* pass = getpass("");
	strcpy(currUser.password, pass);

	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(struct account));

	read(sd,&result,sizeof(result));

	if(!result){
		printf("Invalid login!\nEither your Password didn't match OR your Account is Deleted\n\n");
		chooseOption(sd);
	}
	else{
		printf("Succesfully logged in!\n\n");
	}
	return;
}

void accountActDeact(int sd){
    int select = 1, userID, type;
    bool result;

    write(sd, &select, sizeof(int));

    printf("Enter the user ID to be modified : ");
    scanf("%d", &userID);
    printf("Enter action type\n0: Deactivate Account\n1: Activate Account\n");
    scanf("%d",&type);

    while(type < 0 || type > 1){
        printf("Invalid type!\n");
        printf("Enter action type\n0: Deactivate Account\n1: Activate Account\n");
        scanf("%d",&type);
    }

    write(sd, &userID, sizeof(int));
    write(sd, &type, sizeof(int));

    read(sd,&result,sizeof(result));

	if(!result){
		printf("Error modifying the account ,please re-check the User ID!\n\n");
	}
	else{
		printf("Succesfully modified the account!\n\n");
	}
	showMenu(sd);
    return;
}

void modifyCustomer(int sd){
    int select = 2;
    bool result;

    write(sd, &select, sizeof(int));

    struct account modUser1;
    printf("Enter the User ID : ");
    scanf("%d",&modUser1.userID);

    printf("New Name of the account holder : ");
    scanf("%s",modUser1.name);
    printf("New Password(max 10 characters) : ");
    char* pass = getpass("");
    strcpy(modUser1.password, pass);

    write(sd,&modUser1,sizeof(struct account));

    read(sd, &result, sizeof(result));

    if(!result){
		printf("Error modifying the account ,please re-check the User ID and password!\n\n");
	}
	else{
		printf("Succesfully modified the account!\n\n");
	}

	showMenu(sd);
	return;
}

void balanceEnquiry(int sd){
    float amt;
    int select = 1, len;

    write(sd, &select, sizeof(int));
    len = read(sd, &amt, sizeof(float));

    printf("Available Balance : Rs.");
    printf("%0.2f\n\n",amt);

    showMenu(sd);
    return;
}

void deposit(int sd){
    float amt;
    int select = 2;
    bool result;

    printf("Amount to deposit : Rs.");
    scanf("%f",&amt);

    while(amt <= 0){
        printf("Enter a valid amount!\n");
        printf("Amount to deposit : Rs.");
        scanf("%f",&amt);
    }

    write(sd, &select, sizeof(int));
    write(sd, &amt, sizeof(float));

    read(sd, &result, sizeof(result));

    if(!result){
        printf("Error depositing your money!\n\n");
    }
    else{
        printf("Successfully deposited!\n\n");
    }

    showMenu(sd);
    return;
}

void withdraw(int sd){
    float amt;
    int select = 3;
    bool result;

    printf("Amount to withdraw : Rs.");
    scanf("%f",&amt);

    while(amt <= 0){
        printf("Enter a valid amount!\n");
        printf("Amount to withdraw : Rs.");
        scanf("%f",&amt);
    }

    write(sd, &select, sizeof(int));
    write(sd, &amt, sizeof(float));

    read(sd, &result, sizeof(result));

    if(!result){
        printf("Error withdrawing money, Insufficient balance!\n\n");
    }
    else{
        printf("Successfully withdrew!\n\n");
    }

    showMenu(sd);
    return;
}

void transfer(int sd){
    int select = 4, userID;
    float amt;
    bool result;

    write(sd, &select, sizeof(int));

    printf("Enter the user ID of payee : ");
    scanf("%d", &userID);
    printf("Enter amount : ");
    scanf("%f",&amt);

    while(amt <= 0){
        printf("Enter a valid amount!\n");
        printf("Enter amount : ");
        scanf("%f",&amt);
    }

    write(sd, &userID, sizeof(int));
    write(sd, &amt, sizeof(float));

    read(sd,&result,sizeof(result));

	if(!result){
		printf("Error transferring to the account ,please re-check the User ID!\n\n");
	}
	else{
		printf("Succesfully transferred to the account!\n\n");
	}
	showMenu(sd);
    return;
}

void addLoan(int sd){
    int select = 5, type;
    bool result;
    write(sd, &select, sizeof(int));
    
    struct loan addLoan1;
    addLoan1.custID = currUserID;
    printf("Enter amount : ");
    scanf("%f",&addLoan1.amt);

    write(sd, &addLoan1, sizeof(struct loan));

    read(sd, &result, sizeof(result));

    if(!result){
        printf("Error adding the loan!\n\n");
    }
    else{
        printf("Successfully added the loan entry!\n\n");
    }

    showMenu(sd);
}

void viewLoan(int sd){
    int num, select = 3, userID;
    struct loan currLoan;

    printf("Enter the customer user ID : ");
    scanf("%d",&userID);

    write(sd, &select, sizeof(int));
    write(sd, &userID, sizeof(int));
    if(option == 2){
        int temp = -1;
        write(sd, &temp, sizeof(int));
    }
    else{
        write(sd, &currUserID, sizeof(int));
    }

    read(sd, &num, sizeof(int));

    for(int i=0; i<num; i++){
        read(sd, &currLoan, sizeof(struct loan));

        printf("\n\nloan id : %d\n", currLoan.loanID);
        printf("cust id : %d\n", currLoan.custID);
        printf("amt : %0.2f\n", currLoan.amt);

        if(currLoan.empID == -1){
            printf("empID : not assigned\n");
        }
        else{
            printf("emp ID : %d\n",currLoan.empID);
        }
        
        if(currLoan.granted == -1){
            printf("granted : pending\n\n");
        }
        else if(currLoan.granted == 0){
            printf("granted : rejected\n\n");
        }
        else if(currLoan.granted == 1){
            printf("granted : accepted\n\n");
        }
    }

    showMenu(sd);
    return;
}

void grantLoan(int sd){
    int select = 4, loanID, val;
    bool result;

    printf("Enter loan ID : ");
    scanf("%d",&loanID);

    printf("grant loan : \n0:No\n1:Yes\n");
    scanf("%d",&val);

    write(sd, &select, sizeof(int));
    write(sd, &loanID, sizeof(int));
    write(sd, &currUserID, sizeof(int));
    write(sd, &val, sizeof(int));

    read(sd, &result, sizeof(result));

    if(!result){
        if(val == 0){
            printf("Error while rejecting loan!\n\n");
        }
        else{
            printf("Error while accepting loan!\n\n");
        }
    }
    else{
        if(val == 0){
            printf("Successfully rejected loan!\n\n");
        }
        else{
            printf("Successfully accepted loan!\n\n");
        }
    }

    showMenu(sd);
    return;
}

void assignLoan(int sd){
    int select = 4, loanID, empID;
    bool result;

    printf("Enter loan ID : ");
    scanf("%d",&loanID);

    printf("Enter employee ID : ");
    scanf("%d",&empID);

    write(sd, &select, sizeof(int));
    write(sd, &loanID, sizeof(int));
    write(sd, &empID, sizeof(int));

    read(sd, &result, sizeof(result));

    if(!result){
        printf("Unable to assign loan!\n\n");
    }
    else{
        printf("Successfully assigned loan!\n\n");
    }

    showMenu(sd);
    return;
}

void displayTransactions(int sd){
    // ye baad me likhunga
    int select, len, num, userID;
    struct trans temp;

    if(option == 3){
        printf("Enter customer user ID : ");
        scanf("%d",&userID);

        select = 5;
    }
    else if(option == 4){
        select = 7;
        userID = currUserID;
    }

    write(sd, &select, sizeof(int));
    write(sd, &userID, sizeof(int));
    
    read(sd, &num, sizeof(num));

    for(int i=0; i<num; i++){
        read(sd, &temp, sizeof(struct trans));

        printf("\n\ntransaction ID : %d\n", temp.transID);

        if(temp.type == -1){
            printf("customer id : %d withdrew : Rs.%0.2f\n\n",temp.payeeID, temp.amt);
        }
        else if(temp.type == 1){
            printf("customer id : %d deposited : Rs.%0.2f\n\n",temp.payeeID, temp.amt);
        }
        else if(temp.type == 0){
            printf("Payer ID : %d transferred to Payee ID : %d amount : Rs.%0.2f\n\n",temp.payerID, temp.payeeID, temp.amt);
        }
    }

    showMenu(sd);
    return;
}

void addFeedback(int sd){
    //ye bacha hai
    int select = 8,len;
    bool result;
    struct feedback currFeedback;

    printf("Enter feedback (max 999 characters) :\n");
    len = read(0, currFeedback.buff, sizeof(currFeedback.buff) - 1);

    currFeedback.buff[len] = '\0';

    write(sd, &select, sizeof(int));
    write(sd, &currFeedback, sizeof(struct feedback));
    read(sd, &result, sizeof(result));

    if(!result){
        printf("Error while sending feedback!\n\n");
    }
    else{
        printf("Feedback sent successfully!\n\n");
    }

    showMenu(sd);
    return;
}

void viewFeedback(int sd){
    int select = 5, num;
    struct feedback record;

    write(sd, &select, sizeof(int));
    read(sd, &num, sizeof(int));

    printf("\n");

    for(int i=0; i<num; i++){
        read(sd, &record, sizeof(struct feedback));

        printf("%s\n", record.buff);
    }

    printf("\n");

    showMenu(sd);
    return;
}


#endif