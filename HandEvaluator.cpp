/*
 * HandEvaluator.cpp
 *
 *  Created on: 23-Apr-2019
 *      Author: Anantha Yeshawy
 */

#include <iostream>
#include <vector>
#include <string>
#include "HandEvaluator.h"


using namespace std;

namespace Poker {
	HandEvaluator::HandEvaluator() {
		handinfo = NULL;
		playerinfo = NULL;
	}

	void HandEvaluator::evaluateHand(PlayerInfoType* info, HandInfoType* hinfo) {
		playerinfo = info;
		handinfo = hinfo;
		handinfo->name = playerinfo->name;
		//When there is a Flush or a straight, no other poker combinations are possible (except straight flush).
		//So first check for Flush or straight.
		checkForFlush();
		if (!checkForStraight()) {
			//To handle the case of Ace taking value 1 to form straight sequence "A 2 3 4 5"
			if (playerinfo->values.back() == HIGH_ACE) {
				auto actualvalues = playerinfo->values;
				playerinfo->values.erase(playerinfo->values.end() - 1);
				playerinfo->values.insert(playerinfo->values.begin(), ACE);
				checkForStraight();
				playerinfo->values = actualvalues;
			}
		}

		if ((handinfo->handcombination == FLUSH) || (handinfo->handcombination == STRAIGHT)
			|| (handinfo->handcombination == STRAIGHT_FLUSH)) {
			return;
		}

		if (!checkForRepeatedValues()) {
			//At this point all combinations are checked for. Not much luck there!!
			handinfo->handcombination = HIGH_CARD;
		}
	}

	bool HandEvaluator::checkForRepeatedValues() {
		bool result = false;
		unsigned int numofoccurances = 1;

		for (auto it = playerinfo->values.begin(); it < (playerinfo->values.end()); ++it) {
			if ((it + 1) < playerinfo->values.end()) {
				if (*it == *(it + 1)) {
					++numofoccurances;
					result = true;
					continue;
				}
			}
			switch (numofoccurances) {
			case 1:
				handinfo->cardsnotincomination.push_back(*it);
				break;
			case 2:
				if (handinfo->pairvalue == 0)
					handinfo->pairvalue = *it;
				else
					handinfo->pair2value = *it;
				break;
			case 3:
				handinfo->threeofakindvalue = *it;
				break;
			case 4:
				handinfo->fourofakindvalue = *it;
				break;
			default:
				break;
			}
			numofoccurances = 1;
		}

		if (result)
			analyseRepeatedValueCheckResult();

		return result;
	}

	void HandEvaluator::analyseRepeatedValueCheckResult() {
		if (handinfo->fourofakindvalue != 0) {
			handinfo->handcombination = FOUR_OF_A_KIND;
			return;
		}

		if (handinfo->threeofakindvalue != 0) {
			if (handinfo->pairvalue != 0) {
				handinfo->handcombination = FULL_HOUSE;
			}
			else {
				handinfo->handcombination = THREE_OF_A_KIND;
			}
			return;
		}

		if (handinfo->pairvalue != 0) {
			if (handinfo->pair2value != 0)
				handinfo->handcombination = TWO_PAIRS;
			else
				handinfo->handcombination = PAIR;
			return;
		}
	}

	bool HandEvaluator::checkForStraight() {
		bool result = false;
		for (auto it = playerinfo->values.begin(); it < (playerinfo->values.end() - 1); ++it) {
			if ((*it + 1) != *(it + 1)) {
				result = false;
				break;
			}
			result = true;
		}
		if (result) {
			if (handinfo->handcombination == FLUSH)
				handinfo->handcombination = STRAIGHT_FLUSH;
			else
				handinfo->handcombination = STRAIGHT;
			handinfo->laststraightcardvalue = playerinfo->values.back();
		}
		return result;
	}

	bool HandEvaluator::checkForFlush() {
		bool result = false;
		for (auto it = playerinfo->suits.begin(); it < (playerinfo->suits.end() - 1); ++it) {
			if (*it != *(it + 1)) {
				result = false;
				break;
			}
			result = true;
		}
		if (result) {
			handinfo->handcombination = FLUSH;
			handinfo->flushsuit = *(playerinfo->suits.begin());
			//In case the other player also gets a hand of flush, then the values
			//of the cards will determine the winner. 'cardsnotincombination' of
			//both players will be compared.
			handinfo->cardsnotincomination = playerinfo->values;
		}
		return result;
	}

} //namespace

