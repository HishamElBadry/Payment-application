#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "app.h"
#include "../card/card.h"
#include "../app/app.h"
#include "../server/server.h"
#include "../terminal/terminal.h"

extern ST_accountsDB_t accountsDB[255];
extern ST_transaction_t usersDB[255];
extern ST_terminalData_t userInteract_t;
extern ST_cardData_t userInteract_c;
extern uint32_t accountNO;


void cardinfo() {
	printf("Welcome to our payment application \nPlease enter card holder name\n");
	scanf("%[^\n]%*c", &userInteract_c.cardHolderName);
	printf("Please enter your PAN \n");
	scanf("\n");
	scanf("%[^\n]%*c", &(userInteract_c.primaryAccountNumber));
	printf("please enter Expiry date\n");
	scanf("\n");
	scanf("%[^\n]%*c", &(userInteract_c.cardExpirationDate));
}

bool cardTest() {
	if (getCardHolderName(userInteract_c.cardHolderName) != 0) {
		return false;
	}
	else if (getCardExpiryDate(userInteract_c.cardExpirationDate) != 0) {
		return false;
	}
	else if (getCardPAN(userInteract_c.primaryAccountNumber )!= 0) {
		return false;
	}
	else return true;
}

void go_to_terminal() {
	printf("please enter transaction date\n");
	scanf("%[^\n]%*c", &(userInteract_t.transactionDate));
	printf("\n");
	if ( (getTransactionDate(&userInteract_t)) == TERMINAL_OK) {
		
		if (isValidCardPAN(&userInteract_c) == TERMINAL_OK){
	
			if (isCardExpired(userInteract_c, userInteract_t) == TERMINAL_OK ) {
				printf("please enter the transaction amount\n");
				scanf("%f", &userInteract_t.transAmount);
				
		
				 if ( ( getTransactionAmount(&userInteract_t) != TERMINAL_OK)) {
						printf("please enter valid amount\n");
						scanf("%[^\n]%*c", &( userInteract_t.transactionDate) );
				 }
						printf("please enter the max limit amount\n");
						scanf("%f", &userInteract_t.maxTransAmount);
					//printf("%f", userInteract_t.maxTransAmount);
					if  ( setMaxAmount(&userInteract_t) != 0  ) {
						printf("please enter valid amount\n");
					}	
			
				if (isBelowMaxAmount(&userInteract_t) == 0 ){
					go_to_server();
				}
				else {
					printf("the amount excceding the limit \n");
				}
			}
			else {
						printf("the card is expired");
			}
		}
	}
	
}

void go_to_server() {
		if (isValidAccount(&userInteract_c, &userInteract_t) == SERVER_OK) {
			if (isBlockedAccount(&accountsDB) == SERVER_OK) {
				if (isAmountAvailable(&userInteract_t, accountsDB) == SERVER_OK) {
					printf("Successed transaction\n");
					printf("Your balance now is %.1f\n", accountsDB[accountNO].balance);
				}
				else
				{
					printf("DECLINED INSUFFIENT AMOUNT\n");
				}
			}
			else 
			{
				printf("BLOCKED ACCOUNT\n");
			}
		}
		recieveTransactionData(usersDB);
		saveTransaction(usersDB);
		listSavedTransactions();
}

void appStart() {

	
	cardinfo();
	if (cardTest() == 1) {
		go_to_terminal();
	}
	else {
		printf("please check your info again\n");
	}
	

}
