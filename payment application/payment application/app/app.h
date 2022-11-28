#ifndef APP_H_
#define APP_H_

#include<stdio.h>
#include <stdbool.h>
#include "../card/card.h"
#include "../server/server.h"
#include "../terminal/terminal.h"


void appStart();

void cardinfo();

bool cardTest();

void go_to_terminal();

void go_to_server();


#endif // !app.h
