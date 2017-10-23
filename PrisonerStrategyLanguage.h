// Description: Contains various constants and enumerations
// specific to the Prisoner Strategy Interpretation Language (PSL)
// Author: Philip Jones
// Date: 14/10/2017
#pragma once

#include <map>
#include <string>
#include <vector>


namespace PSL
{
	// All possible units "NodeTypes" which form the syntax of PSL
	enum TokenType { 
		KEYWORD,		// Language keywords e.g. IF
		OUTCOME,		// Result of a strategy e.g. BETRAY
		BINARY_OP,		// Binary operation e.g. PLUS
		VARIABLE,		// Language defined variable e.g. ALL_OUTCOMES_W
		INTEGER,		// Integer constant
		LINE_NO,		// Line number
		INVALID_TOKEN	// Token not allowed by the language
	};

	// Helper enum used to quickly commpare values
	enum TokenValue {
		// Key Words
		IF, GOTO,

		// Outcomes
		BETRAY, SILENCE, RANDOM,

		// Binary Operations
		PLUS, MINUS, LESS_THAN, GREATER_THAN, EQUAL_TO,

		// Variables
		LASTOUTCOME,		// Holds outcome of the last game (W, X, Y, Z)
		W,					// I stayed silentand the other prisoner stayed silent
		X,					// I stayed silent but was betrayed by the other prisoner
		Y,					// I betrayed and the other prisoner stayed silent
		Z,					// I betayed and the other prisoner betrayed
		ALLOUTCOMES_W,		// Running total of W outcomes in current game
		ALLOUTCOMES_X, 		// Running total of X outcomes in current game
		ALLOUTCOMES_Y,		// Running total of Y outcomes in current game
		ALLOUTCOMES_Z,		// Running total of Z outcomes in current game
		ITERATIONS,			// Current number of iterations in this game
		MYSCORE				// Cumulative total of years sentenced
	};	

	// Map of words allowed by the language. Useful for quickly identifying enumerator of valid language words
	const std::map<std::string, TokenValue> keywordDictionary = { { "IF", IF }, { "GOTO", GOTO } };
	const std::map<std::string, TokenValue> outcomeDictionary = { { "BETRAY", BETRAY }, { "SILENCE", SILENCE }, { "RANDOM", RANDOM } };
	const std::map<std::string, TokenValue> operatorDictionary = { { "+", PLUS }, { "-", MINUS }, { "<", LESS_THAN }, { ">", GREATER_THAN },
	{ "=", EQUAL_TO } };
	const std::map<std::string, int> variableDictionary = { { "LASTOUTCOME", LASTOUTCOME }, { "W", W }, { "X", X }, { "Y", Y },
	{ "Z", Z }, { "ALLOUTCOMES_W", ALLOUTCOMES_W }, { "ALLOUTCOMES_X", ALLOUTCOMES_X }, { "ALLOUTCOMES_Y", ALLOUTCOMES_Y },
	{ "ALLOUTCOMES_Z", ALLOUTCOMES_Z }, { "ITERATIONS", ITERATIONS }, { "MYSCORE", MYSCORE } };

	// Dictionaries used by the strategy generator
	const std::vector<std::string> charVariables = { "W", "X", "Y", "Z" };
	const std::vector<std::string> variables = { "ALLOUTCOMES_W", "ALLOUTCOMES_X", "ALLOUTCOMES_Y", "ALLOUTCOMES_Z", "ITERATIONS", "MYSCORE" };
	const std::vector<std::string> outcomes = { "BETRAY", "SILENCE", "RANDOM" };
	const std::vector<std::string> relationalOps = { ">", "<", "=" };
	const std::vector<std::string> arithmeticOps = { "+", "-" };
	//TODO: Refactor repetition oir at least variable names
}


typedef PSL::TokenType TokenType;
typedef PSL::TokenValue TokenValue;


typedef std::map<TokenValue, int* const>  IntMap;
typedef std::map<TokenValue, char* const> CharMap;