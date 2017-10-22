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

int Expression::Parse(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars){

	if (m_tokens.begin()->IsCharVariable()){
		return ParseCharExpression(charVars);
	}
	else{
		return ParseNonCharExpression(intVars);
	}
}

int Expression::ParseCharExpression(const std::map<TokenValue, char*>& charVars){
	TokenValue variable = (TokenValue) m_tokens[0].GetValue();
	return *(charVars.at(variable));
}
int Expression::ParseNonCharExpression(const std::map<TokenValue, int*>& intVars){
	// Int expressions
	int position = 0;		// Position in the expression
	int runningSum = 0;		// 
	
	runningSum += GetIntegerValue(intVars, position);

	while (m_tokens.size() > 1 && position < (m_tokens.size() - 2)){
		switch (m_tokens[position + 1].GetValue()){
		case TokenValue::PLUS:	//TODO: Need to update this bit if define PSL++
			runningSum += GetIntegerValue(intVars, position);
			break;
		case TokenValue::MINUS:
			runningSum -= GetIntegerValue(intVars, position);
			break;
		}
		position += 2; //TODO: Magic numbers
	}
	return runningSum;
}

int Expression::GetIntegerValue(const std::map<TokenValue, int*>& intVars, int position){
	if (m_tokens[position].GetType() == TokenType::INTEGER){
		return m_tokens[position].GetValue();
	}
	else{
		TokenValue variable = (TokenValue)m_tokens[position].GetValue();
		return *(intVars.at(variable));
	}

}

