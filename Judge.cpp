/*
 * Judge.cpp
 *
 *  Created on: 23-Apr-2019
 *      Author: Anantha Yeshaswy
 */

#include <iostream>
#include <vector>
#include "Judge.h"

using namespace std;

namespace Poker {
	//Judge *Judge::instance;

	Judge::Judge() {
		winnerinfo = NULL;
		player1 = NULL;
		player2 = NULL;
		valueToCardName[1] = "Ace";
		valueToCardName[2] = "2";
		valueToCardName[3] = "3";
		valueToCardName[4] = "4";
		valueToCardName[5] = "5";
		valueToCardName[6] = "6";
		valueToCardName[7] = "7";
		valueToCardName[8] = "8";
		valueToCardName[9] = "9";
		valueToCardName[10] = "10";
		valueToCardName[11] = "Jack";
		valueToCardName[12] = "Queen";
		valueToCardName[13] = "King";
		valueToCardName[14] = "Ace";

		valueToCombinationName[HIGH_CARD] = "high card";
		valueToCombinationName[PAIR] = "pair";
		valueToCombinationName[TWO_PAIRS] = "two pairs";
		valueToCombinationName[THREE_OF_A_KIND] = "three of a kind";
		valueToCombinationName[STRAIGHT] = "straight";
		valueToCombinationName[FLUSH] = "flush";
		valueToCombinationName[FULL_HOUSE] = "full house";
		valueToCombinationName[FOUR_OF_A_KIND] = "four of a kind";
		valueToCombinationName[STRAIGHT_FLUSH] = "straight flush";
	}

	void Judge::decideWinner(HandInfoType* handinfo) {
		winnerinfo = NULL;

		player1 = &handinfo[0];
		player2 = &handinfo[1];

		if (player1->handcombination > player2->handcombination) {
			winnerinfo = player1;
			printWinner();
		}
		else if (player1->handcombination == player2->handcombination) {
			analyseEqualCombination();
		}
		else {
			winnerinfo = player2;
			printWinner();
		}
	}

	void Judge::analyseEqualCombination() {

		switch (player1->handcombination) {
		case STRAIGHT_FLUSH:
			if (player1->laststraightcardvalue > player2->laststraightcardvalue)
				winnerinfo = player1;
			else if (player1->laststraightcardvalue < player2->laststraightcardvalue)
				winnerinfo = player2;
			else {
				printTie();
				break;
			}
			printWinner();
			break;
		case FOUR_OF_A_KIND:
			if (player1->fourofakindvalue > player2->fourofakindvalue)
				winnerinfo = player1;
			else if (player1->fourofakindvalue < player2->fourofakindvalue)
				winnerinfo = player2;
			else {
				deduceHighCard();
				break;
			}
			printWinner();
			break;
		case FULL_HOUSE:
		case THREE_OF_A_KIND:
			if (player1->threeofakindvalue > player2->threeofakindvalue)
				winnerinfo = player1;
			else if (player1->threeofakindvalue < player2->threeofakindvalue)
				winnerinfo = player2;
			printWinner();
			break;
		case FLUSH:
			deduceHighCard();
			break;
		case STRAIGHT:
			if (player1->laststraightcardvalue > player2->laststraightcardvalue)
				winnerinfo = player1;
			else if (player1->laststraightcardvalue < player2->laststraightcardvalue)
				winnerinfo = player2;
			else {
				printTie();
				break;
			}
			printWinner();
			break;
		case TWO_PAIRS:
			if (player1->pair2value > player2->pair2value)
				winnerinfo = player1;
			else if (player1->pair2value < player2->pair2value)
				winnerinfo = player2;
			else {
				if (player1->pairvalue > player2->pairvalue)
					winnerinfo = player1;
				if (player1->pairvalue < player2->pairvalue)
					winnerinfo = player2;
				else {
					deduceHighCard();
					break;
				}
			}
			printWinner();
			break;
		case PAIR:
			if (player1->pairvalue > player2->pairvalue)
				winnerinfo = player1;
			else if (player1->pairvalue < player2->pairvalue)
				winnerinfo = player2;
			else {
				deduceHighCard();
				break;
			}
			printWinner();
			break;
		case HIGH_CARD:
			deduceHighCard();
			break;
		default:
			break;

		}
	}

	void Judge::deduceHighCard() {
		for (auto it1 = player1->cardsnotincomination.rbegin(), it2 = player2->cardsnotincomination.rbegin();
			it1 < player1->cardsnotincomination.rend(), it2 < player2->cardsnotincomination.rend();
			++it1, ++it2) {
			if (*it1 == *it2)
				continue;
			else if (*it1 > * it2) {
				winnerinfo = player1;
				winnerinfo->winninghighcardvalue = *it1;
				printWinner();
				return;
			}
			else {
				winnerinfo = player2;
				winnerinfo->winninghighcardvalue = *it2;
				printWinner();
				return;
			}
		}
		printTie();
	}

	void Judge::printWinner() {
		cout << winnerinfo->name << " wins. - ";
		if (winnerinfo->handcombination == HIGH_CARD)
			cout << "with " << valueToCombinationName[winnerinfo->handcombination]
			<< ": " << valueToCardName[winnerinfo->winninghighcardvalue] << endl;
		else
			cout << "with " << valueToCombinationName[winnerinfo->handcombination] << endl;
	}

	void Judge::printTie() {
		cout << "Tie." << endl;
	}

} //namespace


