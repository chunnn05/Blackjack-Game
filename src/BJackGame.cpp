/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
  NAME
  BJackGame.cc
  PURPOSE

  NOTES

  AUTHOR
  Tsai-Yen Li (li@cs.nccu.edu.tw)
  HISTORY
  Tsai-Yen Li - Oct 12, 1998: Created.
 ***************************************************************************/

/* $Log:$ */

#include <iostream>
#include "AnsiPrint.h"
#include "Card.h"
#include "BJackGame.h"
#include "BJackPlayer.h"
#include "BJackDealer.h"

using namespace std;
void PrintMyID(const char *studId);
// only constructor
// Must be given a valid (initialized) game player and dealer
// Menu is constructed internally to provide basic text interface
// We must use an initialization list here.
BJackGame::BJackGame(BJackPlayer &bjp, BJackDealer &bjd) : menu(sizeof(menuItems)/sizeof(char *), menuItems), 
	bjplayer(bjp), 
	bjdealer(bjd),
	playerCredit(initCredit), 
	dealerCredit(initCredit), 
	gameOver(true) {


	}

// one run of the game
// take and process a user action
// show current hands for both players at the end of a run.
bool
BJackGame::oneRun() {
	menu.print();
	int choice = menu.getAnswer();




	if (gameOver && choice != o_restart && choice != o_quit) {
		cout << "Game Over" << endl;
		return true;
	}




	switch (choice) {
		case o_more:
			moreCard();
			break;
		case o_enough:
			enough();
			break;
		case o_restart:
			restart();
			break;
		case o_quit:
			quit();
			return false;
	}
	bjplayer.showCards();
	bjdealer.showCards();
	return true;
}

// give the player one more card
// check if we can do that first
void 
BJackGame::moreCard() {
	if (bjplayer.totalPoints() > 21) {
		cout << "You are over 21 already" << endl;
		return;
	}

	int cardID = bjdealer.giveCard();
	Card newCard(cardID);
	bjplayer.addCard(newCard);
}

// give the dealer enough cards to try to win the player
// determine who win the game at the end
void 
BJackGame::enough() {
	bjdealer.openFirstCard();
	bjdealer.addCards(bjplayer.totalPoints());

	result r = bjdealer.judge(bjplayer.totalPoints());

	if (r == win) {
		playerCredit=playerCredit-betCredit;
		dealerCredit=dealerCredit+betCredit;
		cout << "I win. Try again.(You have "<<playerCredit<< " Credits, I have "<<dealerCredit<<" Credits.)" << endl;
	} else if (r == lose) {
		playerCredit=playerCredit+betCredit;
		dealerCredit=dealerCredit-betCredit;
		cout << "You win. Good job.(You have "<<playerCredit<< " Credits, I have "<<dealerCredit<<" Credits.)" << endl;
	} else {
		cout << "It's a tie!(You have " <<playerCredit<< " Credits, I have "<<dealerCredit<<" Credits.)" << endl;;
	}

    if (playerCredit <= 0) {
    gameOver = true;
} 


	gameOver = true;
}

// restart the game by giving each player two new cards
// need to check if any one broke (bankrupt).
void 
BJackGame::restart() {


	if (playerCredit <= 0) {
		cout << "Sorry. Game over. No loan here." << endl;

		gameOver = true;
		return;
	}

	bjplayer.start();
        bjdealer.start();

        bjplayer.addCard(bjdealer.giveCard());
        bjplayer.addCard(bjdealer.giveCard());

	gameOver = false;
}


void BJackGame::quit() {
	PrintMyID("112703059");
	exit(0);
}
