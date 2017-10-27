// Class: Expression
// Description: Parsing of expressions into C++. An expression is a group of
// tokens that can appear on one side of a relational operator
// Author: Philip Jones
// Date: 14/10/2017

#pragma once

#include <vector>
#include <map>
#include "Token.h"

class Expression
{
public:
	Expression() = delete;
	Expression(const std::vector<Token>& vec); 
	~Expression();

	// Evaluates an expression and returns the result as an integer
	int Parse(const IntMap& intVars, const CharMap& charVars);
private:
	// Vector of tokens making up the expression
	std::vector<Token> m_tokens;

	// Helper Functions for parts
	int ParseCharExpression(const CharMap& charVars);
	int ParseNonCharExpression(const IntMap& intVars);

	// Returns the integer value of the token at index position in m_tokens
	int GetIntegerValue(const IntMap& intVars, int position);
};

