#include "Lexer.h"

// Standard Library Includes
#include <cctype>		// For isdigit()
#include <sstream>

using namespace PSL;

Lexer::Lexer()
{
}


Lexer::~Lexer()
{
}

std::vector<Token> Lexer::Tokenise(const std::string& line) const
{
	std::vector<Token> splitLine;			 // Vector to hold output
	std::stringstream input(line);
	std::string word;					 	 // Temporary buffer string 
	while (input >> word){
		Token t = CreateToken(word);
		if (t.GetType() == INVALID_TOKEN){
			splitLine.clear();
			splitLine.push_back(t);
			return splitLine;
		}
		else{
			splitLine.push_back(t);
		}
	}
	return splitLine;
}

bool Lexer::IsBinaryOperation(const std::string& word) const{
	return (operatorDictionary.find(word) != operatorDictionary.end());
}

bool Lexer::IsOutcome(const std::string& word) const{
	return (outcomeDictionary.find(word) != outcomeDictionary.end());
}

bool Lexer::IsVariable(const std::string& word) const{
	return (variableDictionary.find(word) != variableDictionary.end());
}

bool Lexer::IsKeyword(const std::string& word) const{
	return (keywordDictionary.find(word) != keywordDictionary.end());
}

bool Lexer::IsInteger(const std::string& word) const{
	if (word.empty())
		return false;

	auto iter = word.cbegin();
	if (*iter == '-' || *iter == '+'){
		if (word.size() == 1)
			return false;
		else
			iter++;
	}
		

	for (; iter != word.cend(); ++iter){ // If find non-digit character then not an int
		if (!isdigit(*iter))
			return false;
	}
	return  true;
}

// Creates token with the correct type and value based on string input
Token Lexer::CreateToken(const std::string& word) const{
	if (IsBinaryOperation(word)){
		return Token(BINARY_OP, operatorDictionary.at(word));
	}
	else if (IsVariable(word)){
		return Token(VARIABLE, variableDictionary.at(word));
	}
	else if (IsKeyword(word)){
		return Token(KEYWORD, keywordDictionary.at(word));
	}
	else if (IsOutcome(word)){
		return Token(OUTCOME, outcomeDictionary.at(word));
	}
	else if (IsInteger(word)){
		try{
			return Token(INTEGER, std::stoi(word));
		}
		catch (std::invalid_argument&){
			return Token(INVALID_TOKEN, 0, word);
		}
	}
	else{
		return Token(INVALID_TOKEN, 0, word);
	}
}