#include <stdio.h>
#include "terminal.h"
#include"../card/card.h"
#include <string.h>

ST_terminalData_t userInteract_t;
extern ST_cardData_t userInteract_c;
//EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT;
EN_terminalError_t TermError ;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	//printf("please enter transaction date\n");
	//scanf("%[^\n]%*c",&(userInteract_t.transactionDate));
	
	if (strlen(termData->transactionDate) != 10) {
		TermError = WRONG_DATE;
		//printf("Wrong date format try again\n");
		return TermError;
	}
	if(termData->transactionDate[2]!='/' || termData->transactionDate[5] != '/') {
		TermError = WRONG_DATE;
		//printf("Wrong date format try again\n");
		return TermError;
	}
	if ((termData->transactionDate[3] != '0') && (termData->transactionDate[3] != '1'))
	{
		TermError = WRONG_DATE;
		return TermError;

	}
	if (termData->transactionDate[3] == '1') {
		if ((termData->transactionDate[4] != '0') && (termData->transactionDate[4] != '1') && (termData->transactionDate[4] != '2')) {
		TermError = WRONG_DATE;
		return TermError;
		}
	}
	if ((termData->transactionDate[0] != '0') && (termData->transactionDate[0] != '1') && (termData->transactionDate[0] != '2')&& (termData->transactionDate[0] != '3'))
	{
		TermError = WRONG_DATE;
		return TermError;
	}
	if ((termData->transactionDate[0] == '3')) {
		if ((termData->transactionDate[1] != '0') && (termData->transactionDate[1] != '1')) {
			TermError = WRONG_DATE;
			return TermError;
		}
		else {
			TermError = TERMINAL_OK;
			return TermError;
		}
	}
	
	TermError = TERMINAL_OK;
	return TermError;
	
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	strcpy( termData.transactionDate, userInteract_t.transactionDate);
	strcpy(cardData.cardExpirationDate, userInteract_c.cardExpirationDate);
	

	
	// 06/22 12/10/2022
	if (cardData.cardExpirationDate[3] < termData.transactionDate[8]) {
		TermError = EXPIRED_CARD;
		printf("sorry the card is expired\n");
		return TermError;
	}
	else if (cardData.cardExpirationDate[3] > termData.transactionDate[8]) {
		TermError = TERMINAL_OK;
		return TermError;
	}

	if (cardData.cardExpirationDate[4] < termData.transactionDate[9]) {
		TermError = EXPIRED_CARD;
		printf("sorry the card is expired\n");
		return TermError;
	}
	else if (cardData.cardExpirationDate[4] > termData.transactionDate[9]) {
		TermError = TERMINAL_OK;
		return TermError;
	}

	if (cardData.cardExpirationDate[4] == termData.transactionDate[9] && cardData.cardExpirationDate[3] == termData.transactionDate[8])
	{
		if (cardData.cardExpirationDate[0] < termData.transactionDate[3]) {
			TermError = EXPIRED_CARD;
			printf("sorry the card is expired\n");
			return TermError;
		}
		else if (cardData.cardExpirationDate[1] < termData.transactionDate[4]) {
			TermError = EXPIRED_CARD;
			printf("sorry the card is expired\n");
			return TermError;
		}
	}
	TermError = TERMINAL_OK;
	return TermError;
}
	
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	
	int sum = 0;
	int t = 0;
	for (int i = 0; i < strlen(cardData->primaryAccountNumber); i+=2) {
		sum += cardData->primaryAccountNumber[i];
	}
	for (int i = 1; i < strlen(cardData->primaryAccountNumber); i += 2) {
		t=cardData->primaryAccountNumber[i]*2 ;
		if (t > 9) {
			sum += (1 + (t % 10) );
		}
		else {
			sum += t;
		}
	}
	if (sum % 10 == 0) {
		TermError = TERMINAL_OK;
		printf("The card PAN is valid\n");
		return TermError;
	}
	else {
		TermError = INVALID_CARD;
		printf("This is invalid card PAN\n");
		return TermError;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData){
	//printf("please enter the transaction amount\n");
	//scanf("%f", userInteract_t.transAmount);
	//termData->transAmount =userInteract_t.transAmount ;
	if (termData->transAmount <= 0) {
		TermError = INVALID_AMOUNT;
		//printf("Invalid amount\n");
		return TermError;
	}
	else {
		TermError = TERMINAL_OK;
		return TermError;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData){
	if(termData->transAmount > termData->maxTransAmount) {
		TermError = EXCEED_MAX_AMOUNT;
		return TermError;
	}
	else {
	TermError = TERMINAL_OK;
	return TermError;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData){
	//printf("please enter the max limit amount\n");
	//scanf("%f", userInteract_t.maxTransAmount);
	 termData->maxTransAmount= userInteract_t.maxTransAmount ;
	if (termData->maxTransAmount <= 0) {
		TermError = INVALID_MAX_AMOUNT;
		//printf("Invalid Max amount\n");
		return TermError;
	}
	else {
		TermError = TERMINAL_OK;
		return TermError;
	}
}

void getTransactionDateTest(void) 
{
	printf("please enter transaction date\n");
	scanf("%[^\n]%*c", &userInteract_t.transactionDate);
	if ((getTransactionDate(&userInteract_t)) == TERMINAL_OK) {
		printf("The transaction date is valid\n");
	}
	else {
		printf("WRONG DATE\n");

	}
}

void isCardExpriedTest(void) {
	printf("Please enter your Expiry date \n");
	scanf("%[^\n]%*c", &userInteract_c.cardExpirationDate);
	
	printf("Please enter Transaction date \n");
	scanf("%[^\n]%*c", &userInteract_t.transactionDate);
	if (isCardExpired(userInteract_c, userInteract_t) == TERMINAL_OK) {
		printf("The card is not expired\n");
	}
	else {
		printf("The card is expired\n");
	}
}

void getTransactionAmountTest(void) {
	printf("please enter the transaction amount\n");
	scanf("%f", &userInteract_t.transAmount);
	if (getTransactionAmount(&userInteract_t) == TERMINAL_OK) {
		printf("the amount is valid\n");
	}
	else {
		printf("INVALID AMOUNT\n");
	}
}

void isBelowMaxAmountTest(void) {
	printf("please enter the transaction amount\n");
	scanf("%f", &userInteract_t.transAmount);
	printf("please enter the MAX transaction amount\n");
	scanf("%f", &userInteract_t.maxTransAmount);
	if (isBelowMaxAmount(&userInteract_t) == TERMINAL_OK) {
		printf("below max ammount\n");
	}
	else {
		printf("EXCEED MAX AMOUNT\n");
	}
}

void setMaxAmountTest(void) {
	printf("please enter the MAX transaction amount\n");
	scanf("%f", &userInteract_t.maxTransAmount);
	if (setMaxAmount(&userInteract_t) == TERMINAL_OK) {
		printf("the amount is valid\n");
	}
	else {
		printf("INVALID MAX AMOUNT\n");
	}
}

void isValidCardPANTest(void) {
	printf("Please enter your PAN \n");
	scanf("\n");
	scanf("%[^\n]%*c", &userInteract_c.primaryAccountNumber);
	if (isValidCardPAN(&userInteract_c) == TERMINAL_OK) {
		printf("right PAN \n");
	}
	else {
		printf("INVALID PAN \n");
	}
}
