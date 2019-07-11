/*
 * HandEvaluator.cpp
 *
 *  Created on: 23-Apr-2019
 *      Author: Anantha Yeshaswy
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "PokerType.h"

namespace Poker {

	//HandEvaluator class takes input from 'Hand'class and analyses hand.
	//It identifies the highest valued poker combination that is possible
	//with a given set of cards and places all information in 'handinfo'
	//to judge a winner.
	class HandEvaluator {
	public:
		HandEvaluator();

		void evaluateHand(PlayerInfoType *info, HandInfoType* hinfo);

	private:
		PlayerInfoType* playerinfo;
		HandInfoType* handinfo;

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


