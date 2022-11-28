#include <stdio.h>

#include "card.h"

#define _CRT_SECURE_NO_WARNINGS


EN_cardError_t CardError;
ST_cardData_t userInteract_c;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {

	//printf("please enter card holder name \n");
	//scanf("%[^\n]%*c", &(userInteract_c.cardHolderName));
	
	if ( (strlen(cardData->cardHolderName)) >24 || strlen(cardData->cardHolderName) < 20) {
		CardError = WRONG_NAME;
		return CardError;
	}
	else {
		CardError = CARD_OK;
		return CardError;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {

	//printf("please enter Expiry date\n");
	//scanf("%[^\n]%*c", &(userInteract_c.cardExpirationDate));

	if (  (strlen(cardData->cardExpirationDate) != 5) || (cardData->cardExpirationDate[2] != '/') ){
		CardError = WRONG_EXP_DATE;
		return CardError;
	}
	if ((cardData->cardExpirationDate[0] != '0') && (cardData->cardExpirationDate[0] != '1')) 
	{
		CardError = WRONG_EXP_DATE;
		return CardError;
	
	}
	if (cardData->cardExpirationDate[0] == '1') {
		if ((cardData->cardExpirationDate[1] != '0') && (cardData->cardExpirationDate[1] != '1') && (cardData->cardExpirationDate[1] != '2'))
		{
			CardError = WRONG_EXP_DATE;
			return CardError;

		}

	}
	
	CardError = CARD_OK;
	return CardError;

}

// 02/23  12/23

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	
	//printf("Please enter your PAN \n");
	//scanf("%d", &(userInteract_c.primaryAccountNumber));

	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19) {
		CardError = WRONG_PAN;
		return CardError;
	}
	else {
		CardError = CARD_OK;
		return CardError;

	}
}


void getCardHolderNameTest(void) {
	printf("please enter card holder name\n");
	scanf("\n");
	scanf("%[^\n]%*c", &userInteract_c.cardHolderName);
	if (getCardHolderName(&userInteract_c) == CARD_OK) {
		printf("the name is right format\n");
	}
	else {
		printf("WRONG NAME\n");
	}
}

void getCardExpiryDateTest(void) {
	printf("Please enter your Expiry date \n");
	
	scanf("%[^\n]%*c", &(userInteract_c.cardExpirationDate));
	if(getCardExpiryDate(&userInteract_c) == CARD_OK) {
		printf("the expiry date has right format\n");
	}
	else {
		printf("WRONG expiry date format\n");
	}
}

void getCardPANTest(void) {
	printf("Please enter your PAN \n");
	scanf("\n");
	scanf("%[^\n]%*c", &(userInteract_c.primaryAccountNumber));
	if (getCardPAN(&userInteract_c) == CARD_OK) {
		printf("the PAN has right format\n");
	}
	else {
		printf("WRONG PAN format\n");
	}
}