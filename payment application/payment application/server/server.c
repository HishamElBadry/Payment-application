#include <stdio.h>

#include "server.h"


//SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
//APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR

ST_accountsDB_t accountsDB[255] = { {2000,RUNNING,"826446289173553719"},{150000,BLOCKED,"193755739128466482"},{2000.0, RUNNING, "8989374615436851"},{100000.0, BLOCKED, "5807007076043875"},{1000000.0, RUNNING, "889255614429173376"} };
ST_transaction_t usersDB[255] = { 0 };  //initialize array with zeros

extern ST_terminalData_t userInteract_t;
extern ST_cardData_t userInteract_c;

EN_serverError_t serverError;
uint32_t accountNO = 0;
uint32_t sequence_NO = 0;


EN_transState_t recieveTransactionData(ST_transaction_t* transData) {

	
	if ( (isAmountAvailable(&userInteract_t,accountsDB) ) == SERVER_OK) {
		
		transData->transState = APPROVED;
	}
	else if ( (isAmountAvailable(&userInteract_t, accountsDB)) == LOW_BALANCE) {
		
		transData->transState = DECLINED_INSUFFECIENT_FUND;
	}
	else if (isBlockedAccount(accountsDB) == BLOCKED_ACCOUNT) {
	
		transData->transState = DECLINED_STOLEN_CARD;
	}
	else if ( (isValidAccount(&userInteract_c, accountsDB) ) == ACCOUNT_NOT_FOUND) {
		
		transData->transState = FRAUD_CARD;
	}
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	accountRefrence = accountsDB;
	cardData = &userInteract_c;
	for (accountNO = 0; accountNO < 255; accountNO++) {
		if (strcmp((cardData->primaryAccountNumber), (*(accountRefrence + accountNO)).primaryAccountNumber) == 0){
				//printf("VALID ACCOUNT\n");
				serverError = SERVER_OK;
				return serverError;
				break;
		}
	}
	//printf("%d", accountNO);
	//printf("INVALID ACCOUNT\n");
	serverError = ACCOUNT_NOT_FOUND;
	return serverError;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	accountRefrence = accountsDB;
	if ((*(accountRefrence + accountNO)).state == BLOCKED  ) {
		//printf("the account is blocked\n");
		serverError = BLOCKED_ACCOUNT;
		return serverError;
	}
	else {
		//printf("the account is not blocked\n");
		serverError = SERVER_OK;
		return serverError;
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	
	accountRefrence = accountsDB;
	if ((*(accountRefrence + accountNO)).balance >= termData->transAmount) {
		serverError = SERVER_OK;
		accountsDB[accountNO].balance -= termData->transAmount;
		
		return serverError;
	}
	else {
		serverError = LOW_BALANCE;
	
		return serverError;
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	

		strcpy(transData->cardHolderData.cardHolderName, userInteract_c.cardHolderName);
		strcpy(transData->cardHolderData.cardExpirationDate, userInteract_c.cardExpirationDate);
		strcpy(transData->cardHolderData.primaryAccountNumber, userInteract_c.primaryAccountNumber);
		strcpy(transData->terminalData.transactionDate, userInteract_t.transactionDate);

		transData->terminalData.maxTransAmount  = userInteract_t.maxTransAmount ;
		transData->terminalData.transAmount = userInteract_t.transAmount ;

		transData->transactionSequenceNumber = 1;
	
}



void listSavedTransactions(void) {
	printf("\n\n\nTransaction Sequence Number : %d\n", usersDB[0].transactionSequenceNumber);
	printf("Transaction Date : %s\n",usersDB[0].terminalData.transactionDate);
	printf("Transaction Amount :%.1f\n", usersDB[0].terminalData.transAmount);
	
	if (isBlockedAccount(accountsDB) == BLOCKED_ACCOUNT) {
		printf("Transaction State :STOLEN CARD\n");
	}
	else if ( (isAmountAvailable(&userInteract_t, accountsDB)) == LOW_BALANCE) {
		printf("Transaction State :DECLINED INSUFFECIENT FUND TRANSACTION\n");
	}
	else if ( (isAmountAvailable(&userInteract_t, accountsDB)) == SERVER_OK) {
		printf("Transaction State : APPROVED \n");
	}
	else if ((isValidAccount(&userInteract_c, accountsDB)) == ACCOUNT_NOT_FOUND) {
		printf("Transaction State :ACCOUNT NOT FOUND\n");
	}
	
	printf("Terminal Max Amount :%.1f\n",usersDB[0].terminalData.maxTransAmount);
	printf("Cardholder Name : %s \n",usersDB[0].cardHolderData.cardHolderName);
	printf("PAN: %s \n",usersDB[0].cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date :%s \n",usersDB[0].cardHolderData.cardExpirationDate);
}

void isValidAccountTest(void) {
	printf("Please enter your PAN \n");
	scanf("\n");
	scanf("%[^\n]%*c", &(userInteract_c.primaryAccountNumber));
	if (isValidAccount(&userInteract_c, accountsDB) == SERVER_OK) {
		printf("VALID ACCOUNT\n");
	}
	else {
		printf("INVALID ACCOUNT\n");
	}
}

void isBlockedAccountTest(void) {
	printf("Please enter your PAN \n");
	scanf("\n");
	scanf("%[^\n]%*c", &(userInteract_c.primaryAccountNumber));
	if (isValidAccount(&userInteract_c, accountsDB) == SERVER_OK) {
		if (isBlockedAccount(&accountsDB) == SERVER_OK) {
			printf("UNBLOCKED ACCOUNT\n");
		}
		else {
			printf("BLOCKED ACCOUNT\n");
		}
	}
	else {
		printf("INALID ACCOUNT\N");
	}

}

void isAmountAvailableTest(void) {
	printf("Please enter your PAN \n");
	scanf("\n");
	scanf("%[^\n]%*c", &(userInteract_c.primaryAccountNumber));
	printf("Please enter transaction amount \n");
	scanf("%f", &(userInteract_t.transAmount));
	if (isValidAccount(&userInteract_c, accountsDB) == SERVER_OK) {
		if (isBlockedAccount(&accountsDB) == SERVER_OK) {
			if (isAmountAvailable(&userInteract_t, accountsDB) == SERVER_OK) {
				printf("APPROVED\n");
			}
			else {
				printf("LOW BALANCE\n");
			}
		}
	}
}
