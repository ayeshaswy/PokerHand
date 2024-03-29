/*
 * InputHandler.cpp
 *
 *  Created on: 24-Apr-2019
 *      Author: Anantha Yeshaswy
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "InputHandle.h"


using namespace std;

namespace Poker {
	InputHandle::InputHandle(std::string file):inputFile(file){
		infile.open(inputFile.c_str(), ios_base::in);
		if (infile.fail()) {
			cout << "Could not open file" << endl;
			cout << "Make sure to give correct file name and path" << endl << endl;
			throw InvalidInputException("Unable to Open file");
		}
	}

	bool InputHandle::readFileForInput(PlayerInfoType** playerinfo) {
		string line, token, temp;
		size_t pos = 0;
		string delimiter = " ";
		vector<string> inputfields;
		static bool test = false;

		if (infile.is_open()) {
			while (!infile.eof()) {
				getline(infile, line);
				ltrim(line);
				rtrim(line);
				if (line.empty()) {
					continue;
				}
				if (isLineComment(line)) {
					continue;
				}
				rtrim(line); // If comment was made in the input file at the end of actual input line
							 // then we delete everything after the input data.
				temp = line; //saving line to print in case of exception.

				convertToUpper(line);
				while ((pos = line.find(delimiter)) != string::npos) {
					token = line.substr(0, pos);
					inputfields.push_back(token);
					line.erase(0, pos + 1);
				}
				//Pushing back the last card value. It doesn't happen inside above loop as
				//line.find() cannot find delimiter (" ") after the last element.
				inputfields.push_back(line);
				try {
					parseInput(inputfields, playerinfo);
				}
				catch (exception& e) {
					cout << temp << "-->" << e.what() << endl;
					inputfields.clear();
					continue;
				}
				return true;
			}
			infile.close();
			return false;
		}
		else {
			cout << "Something went wrong. Unable to read from file.\n";
		}
		return false;
	}

	void InputHandle::parseInput(vector<string> inputfields, PlayerInfoType** playerinfo) {
		size_t pos;
		string delimiter = ":";
		string player1name, player2name;
		vector<string> player1hand, player2hand;

		for (auto it = inputfields.begin(); it < inputfields.end(); ++it) {
			if ((pos = it->find(delimiter)) != string::npos) {
				if (player1name.empty()) {
					player1name = it->substr(0, pos);
				}
				else {
					player2name = it->substr(0, pos);
				}
				continue;
			}
			if (player2name.empty())
				player1hand.push_back(*it);
			else
				player2hand.push_back(*it);
		}

		checkCardsUniqueness(player1hand, player2hand);
		try {
			processAndValidateCards(player1hand, playerinfo[0]);
			playerinfo[0]->name = player1name;

			processAndValidateCards(player2hand, playerinfo[1]);
			playerinfo[1]->name = player2name;
		}
		catch (exception& e) {
			//processAndValidateCards would have added a few elements in to the vectors in
			//playerinfo array before it recognized some issue with the input. So clear those
			//elements before passing on the exception. This is needed because the file read 
			//function has goes ahead with reading next line and also it does not have access
			//to playerinfo array to clear the data by itself.
			playerinfo[0]->values.clear();
			playerinfo[0]->suits.clear();
			playerinfo[1]->values.clear();
			playerinfo[1]->suits.clear();
			throw InvalidInputException(e.what());
		}

		sort(playerinfo[0]->values.begin(), playerinfo[0]->values.end());
		sort(playerinfo[1]->values.begin(), playerinfo[1]->values.end());
	}

	void InputHandle::checkCardsUniqueness(vector<string> player1hand, vector<string> player2hand) {
		//Check if any card is provided twice in the input.
		//There cannot be 2 cards in a suit with same value.
		int count = 0;
		for (auto it = player1hand.begin(); it < player1hand.end(); ++it) {
			for (auto it1 = player1hand.begin(), it2 = player2hand.begin();
				it1 < player1hand.end() && it2 < player2hand.end(); ++it1, ++it2) {
				if (*it == *it1)
					count++;
				if (*it == *it2)
					count++;
				if (count > 1) {
					throw InvalidInputException("More than one occurrence of one or more card in the input");
				}
			}
			count = 0;
		}

		for (auto it = player2hand.begin(); it < player2hand.end(); ++it) {
			for (auto it1 = player1hand.begin(), it2 = player2hand.begin();
				it1 < player1hand.end() && it2 < player2hand.end(); ++it1, ++it2) {
				if (*it == *it1)
					count++;
				if (*it == *it2)
					count++;
				if (count > 1) {
					throw InvalidInputException("More than one occurrence of one or more card in the input");
				}
			}
			count = 0;
		}
	}

	void InputHandle::processAndValidateCards(vector<string> playerhand, PlayerInfoType* player) {
		stringstream sstr;

		//Check if both hands have exactly 5 cards each.
		if (playerhand.size() != 5) {
			throw InvalidInputException("The number of cards in hand is not equal to 5");
		}

		for (auto i : playerhand) {
			int numofcharsincard = i.length();

			if ((numofcharsincard < 2) || (numofcharsincard > 3)) {
				throw InvalidInputException("Wrong number of characters per card in the input");
			}

			if (numofcharsincard == 3) {
				if (!isdigit(i[0]) || !isdigit(i[1]))
					throw InvalidInputException("Invalid value for card, first 2 out of 3 chars are not digits");
			}

			if (i[0] == 'J')
				player->values.push_back(JACK);
			else if (i[0] == 'Q')
				player->values.push_back(QUEEN);
			else if (i[0] == 'K')
				player->values.push_back(KING);
			else if (i[0] == 'A')
				player->values.push_back(HIGH_ACE);
			else if (isdigit(i[0])) {
				if (i.length() == 2) {
					sstr.str(i.substr(0, 1));
				}
				else {
					//This else part is executed only when the value of card is 10S or 10H
					//or 10D or 10C. user will be notified with error if 11, 12, 13... is input.
					sstr.str(i.substr(0, 2));
				}

				int num = 0;
				sstr >> num;
				if ((num < 2) || (num > 10)) {
					throw InvalidInputException("Card with value less than 2 or greater than 10.");
				}
				player->values.push_back(num);
				sstr.clear();
			}
			else {
				throw InvalidInputException("Invalid card with value not among 2-10/J/Q/K/A");
			}

			string suit;
			if (i.length() == 2)
				suit = i.substr(1, 1);
			else
				suit = i.substr(2, 1);

			if (suit == "C")
				player->suits.push_back(CLUBS);
			else if (suit == "D")
				player->suits.push_back(DIAMONDS);
			else if (suit == "H")
				player->suits.push_back(HEARTS);
			else if (suit == "S")
				player->suits.push_back(SPADES);
			else {
				throw InvalidInputException("Invalid suit for a card. Not among C/D/H/S");
			}
		}
	}

	void InputHandle::ltrim(string& line) {
		string whitespace = " \t\n\r";
		size_t pos;

		if ((pos = line.find_first_not_of(whitespace)) != string::npos)
			line.erase(0, pos);
		else
			line = "";
	}

	void InputHandle::rtrim(string& line) {
		string whitespace = " \t\n\r";
		size_t pos;

		if ((pos = line.find_last_not_of(whitespace)) != string::npos)
			line.erase(pos + 1, line.length() - 1);
		else
			line = "";
	}

	bool InputHandle::isLineComment(string& line) {
		string delimiter = "#";
		size_t pos;

		if ((pos = line.find(delimiter)) != string::npos) {
			if (pos == 0)
				return true;
			else
				line = line.substr(0, pos);
		}
		return false;
	}

	void InputHandle::convertToUpper(string& line) {
		for (unsigned int i = 0; i < line.length(); i++) {
			if (!isdigit(line[i])) {
				line[i] = toupper(line[i]);
			}
		}
	}
} //namespace