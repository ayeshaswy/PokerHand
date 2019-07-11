/*
 * PokerVaribles.hpp
 *
 *  Created on: 23-Apr-2019
 *      Author: Anantha Yeshaswy
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <mutex>
#include <condition_variable>

namespace Poker {

#define CLUBS			1
#define DIAMONDS		2
#define HEARTS			3
#define SPADES			4

#define ACE				1
#define TWO				2
#define THREE			3
#define FOUR			4
#define FIVE			5
#define SIX				6
#define SEVEN			7
#define EIGHT			8
#define NINE			9
#define TEN				10
#define JACK			11
#define QUEEN			12
#define KING			13
#define HIGH_ACE		14

	enum PokerCombinations {
		HIGH_CARD,
		PAIR,
		TWO_PAIRS,
		THREE_OF_A_KIND,
		STRAIGHT,
		FLUSH,
		FULL_HOUSE,
		FOUR_OF_A_KIND,
		STRAIGHT_FLUSH,
	};

	// Structure to store all poker hand related information that is needed
	// to judge the winner.
	struct HandInfoType {
		std::string name;
		PokerCombinations handcombination = HIGH_CARD; 	//Hand combination such as PAIR/STRAIGHT/FULSH etc.
		unsigned int pairvalue = 0;				//value of pair. eg - pair of 3 or pair of Aces.
		unsigned int pair2value = 0; 			// value of a second pair if exists.
		unsigned int threeofakindvalue = 0; 	//value of card forming 3 of a kind.
		unsigned int fourofakindvalue = 0; 		// value of card forming four of a kind.
		unsigned int laststraightcardvalue = 0;	//value of last card in straight.
		unsigned int winninghighcardvalue = 0; 	//value of the card that decides winner in case of equal-
											//-combination of both player's hands or in case of high.
		unsigned int flushsuit = 0; 			//name of the suit that forms flush.
		std::vector<unsigned int> cardsnotincomination; // All cards that are not part of a combination.
														// In case of no combination(i.e. high card case)
														//all 5 cards will be in the list.
	};

	struct PlayerInfoType {
		std::string name;					//Name of the player. Black/White or any other name this is provided.
		std::vector<unsigned int> suits;	//Vector holding suit information of each card of a player.
		std::vector<unsigned int> values;	//Vector holding value information of each card of a payer.
	};

} //namespace
