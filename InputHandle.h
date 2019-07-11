/*
 * InputHandler.hpp
 *
 *  Created on: 24-Apr-2019
 *      Author: Anantha Yeshaswy
 */

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include "PokerType.h"

namespace Poker {

	//Handles inputs from both stdin and file. Reads the input,
	//analyses, processes to make it usable by other involved classes,
	//validates and saves the information in PlayerInfoType object.
	class InputHandle {
	public:
		//read in put from a given file.
		bool readFileForInput(PlayerInfoType** playerinfo);

		InputHandle(std::string file);

	private:
		//PlayerInfoType *player1, *player2;
		std::ifstream infile;
		std::string inputFile;

		//void clearPlayerInfo();

		void ltrim(std::string& line);
		void rtrim(std::string& line);

		//check if the line read from a file is a comment. If it is indeed a comment,
		//Ignore and read the next line. If the input is valid followed by a comment
		//in the same line, then remove the comment part in the input line.
		bool isLineComment(std::string& line);

		void convertToUpper(std::string& line);

		//Parse the raw string input into usable format for hand evaluation and judgement
		//of winner.
		void parseInput(std::vector<std::string> inputfields, PlayerInfoType** playerinfo);

		//Check if a given card in the input is not repeated.
		void checkCardsUniqueness(std::vector<std::string> player1hand, std::vector<std::string> player2hand);

		//Called from with in parseInput(). Validates the input and throws exceptions in
		//case of discrepancies.
		void processAndValidateCards(std::vector<std::string> playerhand, PlayerInfoType* player);
	};


	//Exception used for notifying discrepancies in the input.
	class InvalidInputException : public std::exception {
		char* err;
		virtual const char* what() const throw()
		{
			return err;
		}
	public:
		InvalidInputException(const char* msg) {
			err = (char*)msg;
		}
	};

} //namespace
