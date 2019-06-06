/*
 * JudgeWinner.hpp
 *
 *  Created on: 23-Apr-2019
 *      Author: Anantha Yeshaswy
 */

#ifndef JUDGE_HPP_
#define JUDGE_HPP_

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "PokerType.hpp"


namespace Poker {
class Judge {
public:
	//exposed wrapper function to call for decision on the winner.
	void decideWinner();

	void resetJudgeData();
	void setHandInfo(const HandInfoType info1, const HandInfoType info2);
	static Judge* getInstance() {
		if (instance == NULL) {
			instance = new Judge();
		}
		return instance;
	}
private:
	static Judge *instance;
	std::map<int,std::string> valueToCardName;
	std::map<PokerCombinations, std::string> valueToCombinationName;
	HandInfoType *player1, *player2, *winnerinfo;

	Judge();

	//Print winner in case we have a clear winner.
	void printWinner();

	//Print function to print output when its tie.
	void printTie();

	//In case both players have same combination, this function is called to
	//analyse the combinations further and decide winner.
	void analyseEqualCombination();

	//Function to decide winner by High card. Used the field 'cardsnotincombination'
	// of 'handinfo' structure.
	void deduceHighCard();

};
}//namespace


#endif /* JUDGE_HPP_ */
