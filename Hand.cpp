/*
 * Hand.cpp
 *
 *  Created on: 23-Apr-2019
 *      Author: Anantha Yeshaswy
 */

#include <iostream>
#include <vector>
#include <string>
#include "Hand.hpp"

using namespace std;

namespace Poker {

Hand::Hand(const PlayerInfoType info) {
	handinfo.fourofakindvalue = 0;
	handinfo.handcombination = HIGH_CARD;
	handinfo.laststraightcardvalue = 0;
	handinfo.pair2value = 0;
	handinfo.pairvalue = 0;
	handinfo.threeofakindvalue = 0;
	handinfo.winninghighcardvalue = 0;
	playerinfo = info;
}

PlayerInfoType Hand::getPlayerInfo(){
	return playerinfo;
}

HandInfoType Hand::getHandInfo(){
	return handinfo;
}

void Hand::setHandInfo(const HandInfoType info){
	handinfo = info;
	handinfo.name = playerinfo.name;
}

}



