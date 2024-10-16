#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>  
#include<arpa/inet.h>  
#include<unistd.h>
#include<stdbool.h>
#include<strings.h>
#include<string.h>

#include"./structs/admin.h"
#include"./structs/account.h"
#include"./structs/loan.h"
#include"./structs/transaction.h"
#include"./structs/feedback.h"

void chooseOption(int); //
void showMenu(int); //

/*
void attemptAdminLogin(int);
void addAccount(int);
void modifyAccount(int);
void viewDetails(int);
void changePassword(int, int);

void attemptOtherLogin(int);
void accountActDeact(int);

void modifyCustomer(int);

void balanceEnquiry(int);
void deposit(int);
void withdraw(int);
void transfer(int);

void viewLoan(int);
void addLoan(int);
void grantLoan(int);
void assignLoan(int);

void displayTransactions(int);
void addFeedback(int);
void viewFeedback(int);
*/

int option, currUserID;

#include"./Func/clientFunc.h"

void chooseOption(int sd){
	printf("1 : Admin Login\n");
    printf("2 : Manager Login\n");
    printf("3 : Employee Login\n");
    printf("4 : Customer Login\n");
	printf("Choose an option : ");
	scanf("%d",&option);
	printf("Option : %d\n\n",option);

	switch(option){
		case 1 :
			attemptAdminLogin(sd);
			break;
        case 2 :
            attemptOtherLogin(sd);
            break;
        case 3 :
            attemptOtherLogin(sd);
            break;
        case 4 :
            attemptOtherLogin(sd);
            break;
		default :
			printf("Invalid option!\n\n");
			chooseOption(sd);
			break;
	}
	return;
}

void showMenu(int sd){
	int type;

    if(option == 1){
        printf("Admin menu :\n");
        printf("1 : Add Account     \n");
        printf("2 : Modify Account  \n");
        printf("3 : View Account    \n");
        printf("4 : Change Password \n");
        printf("5 : Exit            \n");
        
        printf("Choose an option : ");
        scanf("%d",&type);
        printf("Option : %d\n\n",type);

        switch(type){
            case 1:
                addAccount(sd);
                break;
            case 2:
                modifyAccount(sd);
                break;
            case 3:
                viewDetails(sd); // account info display karna hai
                break;
            case 4:
                changePassword(sd,type);
                break;
            case 5:
                write(sd, &type, sizeof(int));
                printf("Logged out!\n\n");
                exit(0);
            default:
                printf("Invalid option!\n\n");
                showMenu(sd);
                break;
        }
    }
    else if(option == 2){
        printf("Manager menu :\n");
        printf("1 : Activate/Deactivate Account \n");
        printf("2 : Change Password             \n");
        printf("3 : View Loan                   \n");
        printf("4 : Assign Loan                 \n");
        printf("5 : View Feedback               \n");
        printf("6 : Exit                        \n");
        
        printf("Choose an option : ");
        scanf("%d",&type);
        printf("Option : %d\n\n",type);

        switch(type){
            case 1:
                accountActDeact(sd);
                break;
            case 2:
                changePassword(sd,type);
                break;
            case 3:
                viewLoan(sd);
                break;
            case 4:
                assignLoan(sd);
                break;
            case 5:
                viewFeedback(sd);
                break;
            case 6:
                write(sd, &type, sizeof(int));
                printf("Logged out!\n\n");
                exit(0);
            default:
                printf("Invalid option!\n\n");
                showMenu(sd);
                break;
        }
    }
    else if(option == 3){
        printf("Employee menu :\n");
        printf("1 : Add New Customer  \n");
        printf("2 : Modify Customer   \n");
        printf("3 : View Loans        \n");
        printf("4 : Accept/Reject Loan\n");
        printf("5 : View Transactions \n");
        printf("6 : Exit              \n");

        printf("Choose an option : ");
        scanf("%d",&type);
        printf("Option : %d\n\n",type);

        switch(type){
            case 1:
                addAccount(sd);
                break;
            case 2:
                modifyCustomer(sd);
                break;
            case 3:
                viewLoan(sd);
                break;
            case 4:
                grantLoan(sd);
                break;
            case 5:
                displayTransactions(sd);
                break;
            case 6:
                write(sd, &type, sizeof(int));
                printf("Logged out!\n\n");
                exit(0);
            default:
                printf("Invalid option!\n\n");
                showMenu(sd);
                break;
        }
    }
    else if(option == 4){
        printf("Customer menu :\n");
        printf("1 : View Balance      \n");
        printf("2 : Deposit Money     \n");
        printf("3 : Withdraw Money    \n");
        printf("4 : Transfer Funds    \n");
        printf("5 : Take a Loan       \n");
        printf("6 : Change Password   \n");
        printf("7 : View Transactions \n");
        printf("8 : Add Feedback      \n");
        printf("9 : Exit              \n");

        printf("Choose an option : ");
        scanf("%d",&type);
        printf("Option : %d\n\n",type);

        switch(type){
            case 1:
                balanceEnquiry(sd);
                break;
            case 2:
                deposit(sd);
                break;
            case 3:
                withdraw(sd);
                break;
            case 4:
                transfer(sd);
                break;
            case 5:
                addLoan(sd);
                break;
            case 6:
                changePassword(sd,type);
                break;
            case 7:
                displayTransactions(sd);
                break;
            case 8:
                addFeedback(sd);
                break;
            case 9:
                write(sd, &type, sizeof(int));
                printf("Logged out!\n\n");
                exit(0);
            default:
                printf("Invalid option!\n\n");
                showMenu(sd);
                break;
        }
    }
}

int main(){
	printf("Welcome to IIIT Bank\n\n");
	struct sockaddr_in server;    
	int sd,msgLength;
	char buff[50];
	char result;

	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(5555);

	connect(sd,(struct sockaddr *)&server,sizeof(server));
	chooseOption(sd);
	showMenu(sd);
	close(sd);
	return 0;
}