#include <stdio.h>
#include "../payment application/app/app.h"

#define _CRT_SECURE_NO_WARNINGS

extern ST_accountsDB_t accountsDB[255];
extern ST_transaction_t usersDB[255];
extern ST_cardData_t userInteract_c;
extern uint32_t accountNO;


int main() {
	//getCardHolderNameTest();
	//getCardHolderNameTest();
	//
	//
	//getCardExpiryDateTest();
	//getCardExpiryDateTest();
	// 
	// 
	//getCardPANTest();
	//getCardPANTest();
	// 
	// 
	//getTransactionDateTest();
	//getTransactionDateTest();
	// 
	// 
	//isCardExpriedTest();
	//isCardExpriedTest();
	// 
	// 
	//getTransactionAmountTest();
	//getTransactionAmountTest();
	// 
	// 
	//isBelowMaxAmountTest();
	//isBelowMaxAmountTest();
	// 
	// 
	//setMaxAmountTest();
	//setMaxAmountTest();
	// 
	// 
	//isValidCardPANTest();
	//isValidCardPANTest();
	// 
	//isValidAccountTest();
	//isValidAccountTest();
	// 
	// isBlockedAccountTest();
	//isBlockedAccountTest();
	// 
	//isAmountAvailableTest();
	//isAmountAvailableTest() ;
	//


	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 19; j++) {

			printf("%c", accountsDB[i].primaryAccountNumber[j]);
		}
		printf("\n");
	}
	
	
	appStart();
	
	
	
}

