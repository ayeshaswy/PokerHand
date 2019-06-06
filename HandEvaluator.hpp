/*
 * HandEvaluator.cpp
 *
 *  Created on: 23-Apr-2019
 *      Author: Anantha Yeshaswy
 */

#ifndef HANDEVALUATOR_CPP_
#define HANDEVALUATOR_CPP_

#include <iostream>
#include <vector>
#include <string>

#include "PokerType.hpp"

namespace Poker {

//HandEvaluator class takes input from 'Hand'class and analyses hand.
//It identifies the highest valued poker combination that is possible
//with a given set of cards and places all information in 'handinfo'
//to judge a winner.
class HandEvaluator {
public:
	HandInfoType *handinfo;
	void setPlayerInfo(const PlayerInfoType info);
	PlayerInfoType getPlayerInfo();

	static HandEvaluator* getInstance() {
		if (instance == NULL) {
			instance = new HandEvaluator();
		}
		return instance;
	}

	void evaluateHand();
	void resetEvaluatorData();

private:
	HandEvaluator();
	static HandEvaluator *instance;
	PlayerInfoType *playerinfo;

	//checks for pair, 2 pairs, 3 of kind and 4 of a kind.
	bool checkForRepeatedValues();

	//Analyses finding from 'checkForRepeatedValues() method and decides the combination.
	void analyseRepeatedValueCheckResult();

	//checks for straight.
	bool checkForStraight();

	//checks for Flush.
	bool checkForFlush();
};

}



#endif /* HANDEVALUATOR_CPP_ */
