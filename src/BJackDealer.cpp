/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
  NAME
  BJackDealer.cc
  PURPOSE

  NOTES

  AUTHOR
  Tsai-Yen Li (li@cs.nccu.edu.tw)
  HISTORY
  Tsai-Yen Li - Oct 12, 1998: Created.
 ***************************************************************************/

/* $Log:$ */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
}

using namespace std;

#include <iostream>
#include "AnsiPrint.h"
#include "Card.h"
#include "BJackPlayer.h"
#include "BJackDealer.h"
#include <random>

// constructor 
// nDeck is the number of standard decks that the dealer will deal with
BJackDealer::BJackDealer(int nSet) : BJackPlayer("Dealer"), numDecks(nSet), cardIndex(0) {
	start();
}

// distribute a card to the player
int
BJackDealer::giveCard() {
	if (cardIndex >= deck.size()) {
		shuffle();
	}
	Card drawnCard = deck[cardIndex++];
	usedCards.push_back(drawnCard);
	return drawnCard.getID();
}

// give the dealer one card unconditionally
void 
BJackDealer::addCard() {
	BJackPlayer::addCard(Card(giveCard()));
}

// give the dealer as many cards as necessary to exceed the player 
// of the given total points
// A special case happen when both of them have 21 points.
// It is a tie game and therefore the dealer does not get more cards.

void
BJackDealer::addCards(int oppTotal) {
	int dealerPoints = totalPoints();

	if (dealerPoints == 21 && oppTotal == 21)
		return;

	while (dealerPoints < 17 || (dealerPoints <= oppTotal && oppTotal <= 21)) {
		addCard();
		dealerPoints = totalPoints();
	}
}

// Determine who has win the game.
// The total points that the dealer has should be greater than 
// the player at the point this function is called.

result
BJackDealer::judge(int oppTotal) const {
	int dealerTotal = totalPoints();
	if ((oppTotal > 21 && dealerTotal > 21) || (oppTotal == dealerTotal && oppTotal <= 21)) return tie; 
	if (dealerTotal > 21) return lose;  
	if (oppTotal > 21 && dealerTotal >= 17) return win;  
	return (dealerTotal > oppTotal) ? win : lose;
}

// start a new game
// before starting a new game, check if there are enough cards left for 
// the next game.

void
BJackDealer::start(void) {
	if (deck.size() - cardIndex < size_t(17 * numDecks)) {
		deck = usedCards;
		usedCards.clear();
		shuffle();
	}

	BJackPlayer::start();  // 重設 Dealer 的手牌
	addCard();
	addCard();
}

// shuffle the deck of cards
void 
BJackDealer::shuffle(void) {
	deck.clear();
	// 初始化卡牌
	for (int i = 0; i < numDecks; ++i) {
		for (int j = 0; j < kMaxNCards; ++j) {
			deck.push_back(Card(j));
		}
	}


	// Fisher-Yates 洗牌算法
	for (int i = 51; i > 0; i--) {
		int j = rand() % (i + 1);
		swap(deck[i], deck[j]);
	}
	cardIndex = 0;
}

// reset the seed before shuffling
void
BJackDealer::shuffle(long seed) {
	srand(seed); 
	shuffle();


}

// open the dealer's first card 
void 
BJackDealer::openFirstCard(void) {
	BJackPlayer::openFirstCard();
}

// show the dealer's hand to the screen
void 
BJackDealer::showCards(void) const {
	BJackPlayer::showCards();
}

