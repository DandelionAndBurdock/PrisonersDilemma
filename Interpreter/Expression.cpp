#include "Expression.h"
#include <iostream>
Expression::Expression(const std::vector<Token>& vec)
{
	if (vec.empty()){
		std::cout << "Error: Trying to construct empty expression" << std::endl;
	}
	m_tokens = vec;
}


Expression::~Expression()
{
}

int Expression::Parse(const IntMap& intVars, const CharMap& charVars){
	if (m_tokens.begin()->IsCharVariable()){
		return ParseCharExpression(charVars);
	}
	else{
		return ParseNonCharExpression(intVars);
	}
}

int Expression::ParseCharExpression(const CharMap& charVars){
	TokenValue variable = (TokenValue) m_tokens[0].GetValue();
	return *(charVars.at(variable));
}
int Expression::ParseNonCharExpression(const IntMap& intVars){
	int position = 0;		// Position in the expression
	int runningSum = 0;		// Running total for extended expressions of form a + b + c - d +....
	
	runningSum += GetIntegerValue(intVars, position);

	while (m_tokens.size() > 1 && position < (m_tokens.size() - 2)){
		switch (m_tokens[position + 1].GetValue()){
		case TokenValue::PLUS:	
			runningSum += GetIntegerValue(intVars, position);
			break;
		case TokenValue::MINUS:
			runningSum -= GetIntegerValue(intVars, position);
			break;
		}
		position += 2; //TODO: Remove Magic numbers
	}
	return runningSum;
}

int Expression::GetIntegerValue(const IntMap& intVars, int position){
	if (m_tokens[position].GetType() == TokenType::INTEGER){
		return m_tokens[position].GetValue();
	}
	else{
		TokenValue variable = (TokenValue)m_tokens[position].GetValue();
		return *(intVars.at(variable));
	}

}

