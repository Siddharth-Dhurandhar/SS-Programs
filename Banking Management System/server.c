#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h> 
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<fcntl.h>
#include <errno.h>

#include"./structs/admin.h"
#include"./structs/account.h"
#include"./structs/loan.h"
#include"./structs/transaction.h"
#include"./structs/feedback.h"

#include"./Func/loanFunc.h"
#include"./Func/accFunc.h"


bool checkAdmin(struct admin);
bool checkAccount(struct account, int);
void serverTask(int);

bool checkAdmin(struct admin currUser){
	int i=currUser.userID;
	int fd=open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/admin.data",O_RDONLY,0744);
	bool result;
	struct admin temp;

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct admin);    	    
	lock.l_len=sizeof(struct admin);	           
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);

	lseek(fd,(i)*sizeof(struct admin),SEEK_SET); 
	read(fd,&temp,sizeof(struct admin));
	if(!strcmp(temp.password,currUser.password)) result=true;
	else result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

bool checkAccount(struct account currUser, int userType){
	int i=currUser.userID;
	int fd=open("/home/siddharth-dhurandhar/SS-Programs/Banking Management System/Data/account.data", O_RDONLY, 0744);
	bool result;
	struct account temp;

	int fl1;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(i)*sizeof(struct account);    	    
	lock.l_len=sizeof(struct account);	           
	lock.l_pid=getpid();

	fl1=fcntl(fd,F_SETLKW,&lock);

	lseek(fd,(i)*sizeof(struct account),SEEK_SET); 
	read(fd,&temp,sizeof(struct account));
	if((strcmp(temp.password,currUser.password) == 0) && (temp.status == 1) && (userType == temp.accType)) result=true;
	else result=false;

	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return result;
}

void serverTask(int nsd){
	int msgLength,select,type,option,currUserID;
	bool result;
	while(1){
		read(nsd,&option,sizeof(option));
		printf("Option : %d\n",option);

		//option = 1 - admin
		//option = 2 - manager - accType = 0
		//option = 3 - employee - accType = 1
		//option = 4 - customer - accType = 2

		if(option==1){
			struct admin currUser1;
			msgLength=read(nsd,&currUser1,sizeof(struct admin));
			currUserID=currUser1.userID;
			printf("Username : %d\n",currUser1.userID);
			printf("Password : %s\n",currUser1.password);
			result=checkAdmin(currUser1);
			write(nsd,&result,sizeof(result));
		}
		else if(option == 2){
			struct account currUser1;
			msgLength=read(nsd,&currUser1,sizeof(struct account));
			currUserID=currUser1.userID;
			printf("Username : %d\n",currUser1.userID);
			printf("Password : %s\n",currUser1.password);
			result=checkAccount(currUser1, 0);
			write(nsd,&result,sizeof(result));
		}
		else if(option == 3){
			struct account currUser1;
			msgLength=read(nsd,&currUser1,sizeof(struct account));
			currUserID=currUser1.userID;
			printf("Username : %d\n",currUser1.userID);
			printf("Password : %s\n",currUser1.password);
			result=checkAccount(currUser1, 1);
			write(nsd,&result,sizeof(result));
		}
		else if(option == 4){
			struct account currUser1;
			msgLength=read(nsd,&currUser1,sizeof(struct account));
			currUserID=currUser1.userID;
			printf("Username : %d\n",currUser1.userID);
			printf("Password : %s\n",currUser1.password);
			result=checkAccount(currUser1, 2);
			write(nsd,&result,sizeof(result));
		}
		else{
			result=false;
			write(nsd,&result,sizeof(result));
		}
		if(result)	break;
	}

	while(1){
		read(nsd,&select, sizeof(select));
		if(option == 1){
			if(select == 1){
				struct account newUser1;
				read(nsd, &newUser1, sizeof(struct account));
				result = addUser(newUser1, nsd);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 2){
				int userID1, newType;
				read(nsd, &userID1, sizeof(int));
				read(nsd, &newType, sizeof(int));
				result = modifyUser(userID1, newType);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 3){
				int userID1;
				read(nsd, &userID1, sizeof(int));
				struct account user1 = getUser(userID1);
				write(nsd, &user1, sizeof(struct account));
			}
			else if(select == 4){
				int userID1;
				read(nsd, &userID1, sizeof(int));
				char oldPwd[10];
				char newPwd[10];
				read(nsd, oldPwd, sizeof(oldPwd));
				read(nsd, newPwd, sizeof(newPwd));
				result = alterPassword(userID1, newPwd, oldPwd);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 5) break;
		}
		else if(option == 2){
			if(select == 1){
				int userID1, newStatus;
				read(nsd, &userID1, sizeof(int));
				read(nsd, &newStatus, sizeof(int));
				result = modifyStatus(userID1, newStatus);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 2){
				int userID1;
				read(nsd, &userID1, sizeof(int));
				char oldPwd[10];
				char newPwd[10];
				read(nsd, oldPwd, sizeof(oldPwd));
				read(nsd, newPwd, sizeof(newPwd));
				result = alterPassword(userID1, newPwd, oldPwd);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 3){
				//view loan
				int custID, empID, num;
				read(nsd, &custID, sizeof(int));
				read(nsd, &empID, sizeof(int));
				num = numLoan(custID, empID);
				write(nsd, &num, sizeof(int));
				searchLoan(nsd, custID, empID);
			}
			else if(select == 4){
				//assign loan
				int loanID, empID;
				bool result;
				read(nsd, &loanID, sizeof(int));
				read(nsd, &empID, sizeof(int));

				result = mapLoan(loanID, empID);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 5){
				//yaha view feedback
				int num;
				num = numFeedback();
				write(nsd, &num, sizeof(int));
				readFeedback(nsd);
			}
			else if(select == 6) break;
		}
		else if(option == 3){
			if(select == 1){
				struct account newUser1;
				read(nsd, &newUser1, sizeof(struct account));
				result = addUser(newUser1, nsd);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 2){
				struct account modUser1;
				read(nsd, &modUser1, sizeof(struct account));
				result = modifyCust(modUser1);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 3){
				// isme view loan ka karle
				// ek linear search to count the no of 
				// loans for a particular custID
				// send this count
				// dusra linear search to actually send
				// the loan structures, the client 
				// already knows about the no of loans
				// so it will only ask till that no
				int custID, empID, num;
				read(nsd, &custID, sizeof(int));
				read(nsd, &empID, sizeof(int));
				num = numLoan(custID, empID);
				write(nsd, &num, sizeof(int));
				searchLoan(nsd, custID, empID);
			}
			else if(select == 4){
				int loanID, empID, val;
				bool result;
				read(nsd, &loanID, sizeof(int));
				read(nsd, &empID, sizeof(int));
				read(nsd, &val, sizeof(int));
				result = giveLoan(loanID, empID, val);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 5){
				//display transactions
				int userID, num;
				read(nsd, &userID, sizeof(int));
				num = numTransactions(userID);
				write(nsd, &num, sizeof(int));
				viewTransactions(nsd, userID);
			}
			else if(select == 6) break;
		}
		else if(option == 4){
			if(select == 1){
				float amt;
				amt = getBalance(currUserID);
				write(nsd, &amt, sizeof(float));
			}
			else if(select == 2){
				float amt;
				read(nsd, &amt, sizeof(float));
				result = depositMoney(currUserID, amt);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 3){
				float amt;
				read(nsd, &amt, sizeof(float));
				result = withdrawMoney(currUserID, amt);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 4){
				int payeeID;
				float amt;
				read(nsd, &payeeID, sizeof(int));
				read(nsd, &amt, sizeof(float));
				result = transferMoney(currUserID, payeeID, amt);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 5){
				struct loan newLoan1;
				read(nsd, &newLoan1, sizeof(struct loan));
				result = createEntry(newLoan1, nsd);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 6){
				int userID1;
				read(nsd, &userID1, sizeof(int));
				char oldPwd[10];
				char newPwd[10];
				read(nsd, oldPwd, sizeof(oldPwd));
				read(nsd, newPwd, sizeof(newPwd));
				result = alterPassword(userID1, newPwd, oldPwd);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 7){
				// ye baad me likhunga
				int userID, num;
				read(nsd, &userID, sizeof(int));
				num = numTransactions(userID);
				write(nsd, &num, sizeof(int));
				viewTransactions(nsd, userID);
			}
			else if(select == 8){
				bool result;
				struct feedback currFeedback;
				read(nsd, &currFeedback, sizeof(struct feedback));
				result = writeFeedback(nsd, currFeedback);
				write(nsd, &result, sizeof(result));
			}
			else if(select == 9) break;
		}
	}

	close(nsd);
	write(1,"Client session Ended\n",sizeof("Client session Ended\n"));
	return;
}


int main(){
	struct sockaddr_in server,client;
	int sd,nsd,clientLen;
	bool result;
	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;    
	server.sin_addr.s_addr=INADDR_ANY; 
	server.sin_port=htons(5555);
	bind(sd,(struct sockaddr *)&server,sizeof(server));
	listen(sd,5);	     

   	printf("Welcome to Bank\n");
	printf("Waiting for Client to connect\n");
	while(1){
		clientLen = sizeof(client);
		nsd=accept(sd,(struct sockaddr *)&client,&clientLen);

		write(1,"Connected to the client\n",sizeof("Connected to the client\n"));
		if(!fork()){
			close(sd);
			serverTask(nsd);
			exit(0);
		}
		else{
			close(nsd);
		}
	}
	return 0;
}