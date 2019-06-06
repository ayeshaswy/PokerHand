/*
 * gameOfPoker.cpp
 *
 *  Created on: 23-Apr-2019
 *      Author: Anantha Yeshaswy
 */

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "InputHandler.hpp"
#include "Hand.hpp"
#include "HandEvaluator.hpp"
#include "Judge.hpp"

#define BLACK "Black"
#define WHITE "white"

using namespace std;
using namespace Poker;

void play(InputHandle* inputhandle) {
	HandEvaluator *evaluator = HandEvaluator::getInstance();
	Judge *judge = Judge::getInstance();

	PlayerInfoType playersinfo[2];

	//Get player information and hand information from InputHandler.
	inputhandle->getPlayersInfo(playersinfo);

	Hand *player1 = new Hand(playersinfo[0]);
	Hand *player2 = new Hand(playersinfo[1]);

	//Process player1's hand
	evaluator->setPlayerInfo(player1->getPlayerInfo());
	evaluator->evaluateHand();
	player1->setHandInfo(*(evaluator->handinfo));

	evaluator->resetEvaluatorData();

	//Process player2's hand
	evaluator->setPlayerInfo(player2->getPlayerInfo());
	evaluator->evaluateHand();
	player2->setHandInfo(*(evaluator->handinfo));

	//Decide the Winner
	judge->setHandInfo(player1->getHandInfo(), player2->getHandInfo());
	judge->decideWinner();

	//reset Judge class data and HandEvaluator class data.
	evaluator->resetEvaluatorData();
	judge->resetJudgeData();
}

int main() {
	int exitflag = 0;
	InputHandle *inputhandle = InputHandle::getInstance();

	//Applicaiton run in a loop until user presses '0' to exit.
	while(!exitflag) {
		int choice = inputhandle->getInputMethod();
		if (choice == 0) {
			exitflag = 1;
			cout<<endl<<"Bye!"<<endl;
			continue;
		}
		if (choice == 1) {		//Input from stdin
			if (inputhandle->readInputInteractiveMode()) {
				play(inputhandle);
			}
			continue;
		}
		if (choice == 2) {		//Input from file.
			while(inputhandle->readFileForInput()) {
				play(inputhandle);
				cout<<endl;
			}
			continue;
		}

	}
	return 0;
}

