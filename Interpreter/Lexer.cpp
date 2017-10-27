#include "Lexer.h"

// Standard Library Includes
#include <algorithm>	// For find(), find_if()
#include <cctype>		// For isdigit()
#include <sstream>
#include <iostream>

#include "SyntaxAnalyser.h"
#include "../PrisonerStrategyLanguage.h"
using namespace PSL;

Lexer::Lexer() :
m_lastLineNumber(0)
{
}


Lexer::~Lexer()
{
}

//TODO: Add some console output to give progress update

std::unique_ptr<Statement> Lexer::Construct(const std::string& line) 
{
	std::vector<Token> tokens =  MakeTokens(line);
	if (tokens.size() == 1 && tokens[0].GetType() == INVALID_TOKEN){
		std::cout << "Lexer Error: Invalid token detected in " << line << std::endl;
		return std::unique_ptr<Statement>(nullptr);
	}
	else{
		if (SyntaxAnalyser::ValidateLine(tokens)){
			return MakeStatement(tokens);
		}
		else{
			return std::unique_ptr<Statement>(nullptr);
		}
	}
}

std::vector<Token> Lexer::Tokenise(const std::string& line) const //TODO: Now have repeated functionality
{
	std::vector<Token> splitLine;			 // Vector to hold output
	std::stringstream input(line);
	std::string word;					 	 // Temporary buffer string 
	while (input >> word) {
		Token t = CreateToken(word);
		if (t.GetType() == INVALID_TOKEN) {
			splitLine.clear();
			splitLine.push_back(t);
			return splitLine;
		}
		else {
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
			return Token(INTEGER, std::stoi(word));
	}
	else{
		return Token(INVALID_TOKEN, 0, word);
	}
}

bool Lexer::IsValidLineNumber(int lineNumber)
{
	if (m_lastLineNumber <= lineNumber){
		m_lastLineNumber = lineNumber;
		return true;
	}
	else{
		std::cout << "Format Error: Please ensure line numbers are monotonically increasing" << std::endl;
		return false;
	}
}


bool Lexer::GetLineNumber(std::istringstream& input, int& linenumber){
	if (input >> linenumber){
		if (!IsValidLineNumber(linenumber)){
			return false;
		}//TODO:  What happens if this is not a number	
	}
	else{
		std::cout << "Format Error: Check line numbers" << std::endl;
	}
	return true;
}

std::vector<Token> Lexer::MakeTokens(const std::string& line){
	std::vector<Token> splitLine;			// Vector to hold output
	std::istringstream input(line);
	std::string word;				// Temporary buffer string 

	//// Read in line number
	int linenumber;
	if (GetLineNumber(input, linenumber)){
		splitLine.push_back(Token(LINE_NO, linenumber));
	}
	else{
		splitLine.clear();
		splitLine.push_back(Token(LINE_NO, 0, "Invalid Line Number"));
		return splitLine;
	}

	// Read in subsequent tokens
	while (input >> word){
		Token t = CreateToken(word);
		if (t.GetType() == INVALID_TOKEN){
			std::cout << "Lexer Error: " << word << " is not a valid token" << std::endl; //TODO: Dont let program continue
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

//TODO: Refacto-> Restructure for clarity
std::unique_ptr<Statement>  Lexer::MakeStatement(const std::vector<Token>& vec){
	// First token after line number will either be outcome or if
	auto start = vec.begin();
	int lineNumber = start->GetValue();
	start += 1; // Move past line number
	if (start->GetType() == PSL::TokenType::OUTCOME){
		return std::unique_ptr<Statement>(new StatementOutcome(lineNumber, PSL::TokenValue(start->GetValue())));
	}
	else if (start->GetValue() == PSL::TokenValue::IF) { //TODO: Make IF Statement
		start += 1; //Move past IF
		auto relOpIter = std::find_if(start, vec.end(), [](const Token& t) { return t.IsRelOp(); });
		std::vector<Token> lhs = std::vector<Token>(start, relOpIter);
		
		auto actionIter = std::find_if(start, vec.end(), [](const Token& t) { return t.IsAction(); });
		std::vector<Token> rhs = std::vector<Token>(relOpIter + 1, actionIter);
		if (actionIter->GetValue() == PSL::TokenValue::GOTO) {
			Statement* action = new StatementGoto((++actionIter)->GetValue());
			return std::unique_ptr<Statement>(new StatementIf(lineNumber, lhs, rhs, PSL::TokenValue(relOpIter->GetValue()), action));
		}
		else {
			Statement* action = new StatementOutcome(lineNumber, PSL::TokenValue(actionIter->GetValue()));
			return std::unique_ptr<Statement>(new StatementIf(lineNumber, lhs, rhs, PSL::TokenValue(relOpIter->GetValue()), action));
		}
	}
	std::cout << "Parsing Error: Failed to create statement" << std::endl;
}
