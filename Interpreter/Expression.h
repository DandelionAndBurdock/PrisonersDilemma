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
	Expression(); //TODO: No default constructor throw some error if no tokens
	~Expression();

	int Parse(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars);
private:
	std::vector<Token> m_tokens;

	int ParseCharExpression(const std::map<TokenValue, char*>& charVars);
	int ParseNonCharExpression(const std::map<TokenValue, int*>& intVars);

	int GetIntegerValue(const std::map<TokenValue, int*>& intVars, int position);
};

