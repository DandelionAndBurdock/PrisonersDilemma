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

	int Parse(const IntMap& intVars, const CharMap& charVars);
private:
	std::vector<Token> m_tokens;

	int ParseCharExpression(const CharMap& charVars);
	int ParseNonCharExpression(const IntMap& intVars);

	int GetIntegerValue(const IntMap& intVars, int position);
};

