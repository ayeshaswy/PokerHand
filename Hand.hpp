/*
 * Hand.h
 *
 *  Created on: 23-Apr-2019
 *      Author: Anantha Yeshaswy
 */

#ifndef HAND_HPP_
#define HAND_HPP_


#include <iostream>
#include <vector>
#include <string>

#include "PokerType.hpp"

namespace Poker {

//Class Hand stores all information relating to each Hand that is input.
//'playerinfo' is prepared by InputHandler class and provided to Hand Class.
//'handinfo' is prepared by HandEvaluator class and provided to Hand Class.
class Hand{
public:
	void setHandInfo(const HandInfoType info);

	HandInfoType getHandInfo();
	PlayerInfoType getPlayerInfo();

	Hand(const PlayerInfoType info);

private:
	PlayerInfoType playerinfo;
	HandInfoType handinfo;
};

}



#endif /* HAND_HPP_ */
