// Class: Lexer
// Description: Splits an input string into tokens. Identifies invalid
// tokens and the type of valid tokens
// Author: Philip Jones
// Date: 14/10/2017
#pragma once

#include <string>
#include <vector>

#include "../PrisonerStrategyLanguage.h"

#include "Statement.h"
#include "Token.h"
#include <memory>

class Lexer
{
public:
	Lexer();
	~Lexer(); 

	// Takes in one line of input and returns a vector of tokens in the string
	// On finding an invalid token will stop parsing string and return a vector
	// containing only that token
	std::unique_ptr<Statement> Construct(const std::string& line);
	std::vector<Token> Tokenise(const std::string& line) const;

public:
	// Helper functions
	// Returns true if word corresponds to a valid language operation
	bool IsBinaryOperation(const std::string& word) const;
	// Returns true if word corresponds to a valid language outcome
	bool IsOutcome(const std::string& word) const;
	// Returns true if word corresponds to a valid language variable
	bool IsKeyword(const std::string& word) const;
	// Returns true if word corresponds to a valid language keyword
	bool IsVariable(const std::string& word) const;
	// Returns true if word corresponds to an integer constant
	bool IsInteger(const std::string& word) const;

	int m_lastLineNumber; // 

	bool IsValidLineNumber(int linenumber);
	bool GetLineNumber(std::istringstream& input, int& linenumber);

	// Creates token with the correct type and value based on string input
	Token CreateToken(const std::string& word) const;

private:
	std::vector<Token> MakeTokens(const std::string& line);
	std::unique_ptr<Statement>  MakeStatement(const std::vector<Token>&);
};
