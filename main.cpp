#include <iostream>
#include <string>
#include <vector> 
#include <thread>
#include <queue>
#include "PokerType.h"
#include "InputHandle.h"
#include "HandEvaluator.h"
#include "Judge.h"
#include "ThreadControl.h"

using namespace std;
using namespace Poker;


std::queue<PlayerInfoType> playersInfo;
std::queue<HandInfoType> handsInfo;

std::mutex playersMutex, handsMutex;
std::condition_variable playersCv, handsCv;

bool tEvalStop = false;
bool tJudgeStop = false;

void input() {
	string inputfile;
	PlayerInfoType* pinfo[2];
	bool notify = false, tStopRead = false;

	cout << "Enter file name" << endl;
	getline(cin, inputfile);
	if (inputfile.empty()) {
		cout << "filename is empty" << endl;
	}

	InputHandle inHandleObj(inputfile);
	while (!tStopRead) {
		pinfo[0] = new PlayerInfoType;
		pinfo[1] = new PlayerInfoType;
		if (inHandleObj.readFileForInput(pinfo)){
			unique_lock<mutex> plock(playersMutex);
			playersInfo.push(*pinfo[0]);
			playersInfo.push(*pinfo[1]);
		}
		else
			tStopRead = true;
		
		playersCv.notify_all();
		delete pinfo[0];
		delete pinfo[1];
	}
	tEvalStop = true;
}

void evaluate() {
	PlayerInfoType players[2];
	HandInfoType *player1Hand, *player2Hand;
	HandEvaluator handEvalObj;

	while (!tEvalStop || !playersInfo.empty()) {
		{
			unique_lock<mutex> plock(playersMutex);
			if (playersInfo.empty()) {
				// The below condition wait needs to consider may cases:
				// - tEvalStop variabe was false when wait started but turned true while waiting
				// - when wait finishes, playersInfo may be empty or might have new values filled.
				//   If new values are filled and tEvalStop is true, the new values must be processed.
				// - A timed condition wait is necessary here as the state it is important to check 
				//   tEvalStop state. Because if the tEvalStop state changes while waiting, it means 
				//   that input thread as ended and theres no incoming notification to wake up from wait.
				playersCv.wait_for(plock, chrono::microseconds(5), [] {return !tEvalStop || !playersInfo.empty();});
				if (tEvalStop && playersInfo.empty())
					break;
				else if (!tEvalStop && playersInfo.empty())
					continue;
			}

			players[0] = playersInfo.front();
			playersInfo.pop();

			players[1] = playersInfo.front();
			playersInfo.pop();
		}

		player1Hand = new HandInfoType;
		handEvalObj.evaluateHand(&players[0], player1Hand);
		player2Hand = new HandInfoType;
		handEvalObj.evaluateHand(&players[1], player2Hand);
		
		{
			unique_lock<mutex> hlock(handsMutex);
			handsInfo.push(*player1Hand);
			handsInfo.push(*player2Hand);
		}
		handsCv.notify_all();
		delete player1Hand, player2Hand;
	}
	tJudgeStop = true;
}

void declareWinner() {
	HandInfoType playersHand[2];
	Judge judgeObj;

	while (!tJudgeStop || !handsInfo.empty()) {
		{
			unique_lock<mutex> hlock(handsMutex);
			if (handsInfo.empty()) {
				// The below condition wait needs to consider may cases:
				// - tJudgeStop variabe was false when wait started but turned true while waiting
				// - when wait finishes, handsInfo may be empty or might have new values filled.
				//   If new values are filled and tJudgeStop is true, the new values must be processed.
				// - A timed condition wait is necessary here as the state it is important to check 
				//   tJudgeStop state. Because if the tJudgeStop state changes while waiting, it means that 
				//   input thread as ended and theres no incoming notification to wake up from wait.
				handsCv.wait_for(hlock, chrono::microseconds(5), [] {return !tJudgeStop || !handsInfo.empty();});
				if (tJudgeStop && handsInfo.empty())
					break;
				else if (!tJudgeStop && handsInfo.empty())
					continue;
			}
			playersHand[0] = handsInfo.front();
			handsInfo.pop();
			playersHand[1] = handsInfo.front();
			handsInfo.pop();
		}
		judgeObj.decideWinner(playersHand);
	}
}

int main() {
	ThreadControl inThreadObj(input);
	ThreadControl evalThread(evaluate);
	ThreadControl judgeThread(declareWinner);
	return 0;
}