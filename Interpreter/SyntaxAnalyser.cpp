#include "SyntaxAnalyser.h"

#include <algorithm> // For find_if(), count_if()
#include <iostream>
#include <vector>

#include "../PrisonerStrategyLanguage.h"


SyntaxAnalyser::SyntaxAnalyser()
{
}


SyntaxAnalyser::~SyntaxAnalyser()
{
}

bool SyntaxAnalyser::IsArithmeticSubExpression(const std::vector<Token>& provisional){
	//TODO: Define Magic Numbers
	if (provisional.size() == 3){
		if (!provisional[0].IsRValue() || !provisional[2].IsRValue())
			return false;
		if (!provisional[1].IsArithmeticOp())
			return false;
	}
	else {
		return false;
	}
}

bool SyntaxAnalyser::IsConditionalSubExpression(const std::vector<Token>& provisional){
	//TODO: Define Magic Numbers
	if (provisional.size() == 3){
		if (!provisional[0].IsRValue() || !provisional[2].IsRValue())
			return false;
		if (!provisional[1].IsRelOp())
			return false;

		return true;
	}
	
	return false;
}

bool SyntaxAnalyser::TestNonCharExpressionFormat(const std::vector<Token>& provisional) { // Change name e.g. test non char format
	
	if (!(provisional.size() % 2)) // Not possible to form a valid expression with an even number of tokens
		return false;

	int numRelOperators = std::count_if(provisional.begin(), provisional.end(), [](const Token& t){ return t.IsRelOp(); });
	if (numRelOperators != 1){
		return false;
	}

	auto iter = provisional.cbegin();
	while (iter != provisional.cend()){
		//  A valid expression flip-flops between an variable and then a binary operation
		if (!(*iter++).IsRValue()){ //TODO: Variable or RVAlue?
			return false;
		}
		if (iter != provisional.cend()){
			if (!(*iter++).IsBinOp()){
				return false;
			}
		}
	}

	return true;
}

bool SyntaxAnalyser::IsExpression(const std::vector<Token>& provisional){
	if (TestCharExpressionFormat(provisional)){
		return true;
	}
	else{
		return TestNonCharExpressionFormat(provisional);
	}
}


bool SyntaxAnalyser::TestCharExpressionFormat(const std::vector<Token>& provisional){
	if (provisional.size() != 3)
		return false;
	auto lastOutcome = std::find_if(provisional.begin(), provisional.end(), [](const Token& t){ return t.GetValue() == TokenValue::LASTOUTCOME; });
	if (lastOutcome == provisional.end()){
		return false;
	}

	if (provisional[1].GetValue() != TokenValue::EQUAL_TO){
		return false;
	}
	//TODO: Define Magic Numbers
	int lastOuctomeIndex = lastOutcome - provisional.begin(); // Either 0 or 2
	if (!provisional[2 - lastOuctomeIndex].IsCharResult()){
		return false;
	}
		return true;
}


bool SyntaxAnalyser::ValidateLine(const std::vector<Token>& provisional){
	
	if (IsEmptyLine(provisional)){
		PrintError(ErrorCode::EMPTY);
		return false;
	}
	// Remove line number
	const std::vector<Token> code = std::vector<Token>(std::next(provisional.begin()), provisional.end());

	// Can make a quick exit if line starts or ends with a binary operator
	if (IsDanglingBinaryOp(code)){
		PrintError(ErrorCode::DANGLING_BINARY);
		return false;
	}

	// Can make a quick exit if line begins with rValue or ends with a variable
	if (IsDanglingVariable(code)){
		PrintError(ErrorCode::DANGLING_VARIABLE);
		return false;
	}

	if (!IsValidOutcome(code)){
		PrintError(ErrorCode::INVALID_OUTCOME);
		return false;
	}

	if (!IsValidIf(code)){
		PrintError(ErrorCode::INVALID_IF);
		return false;
	}

	if (!IsValidGOTO(code)){
		PrintError(ErrorCode::INVALID_GOTO);
		return false;
	}

	return true;
}


bool SyntaxAnalyser::IsEmptyLine(const std::vector<Token>& provisional){
	return provisional.empty();
}
bool SyntaxAnalyser::IsDanglingBinaryOp(const std::vector<Token>& provisional){
	return (provisional.cbegin()->IsBinOp() || provisional.rbegin()->IsBinOp());
}
bool SyntaxAnalyser::IsDanglingVariable(const std::vector<Token>& provisional){
	return (provisional.cbegin()->IsRValue() || provisional.rbegin()->IsVariable());
}
bool SyntaxAnalyser::IsValidGOTO(const std::vector<Token>& provisional){ //TODO: Function name misleading more like we are checking is not an invalid goto
	std::vector<Token>::const_iterator gotoIter = std::find_if(provisional.cbegin(), provisional.cend(), [](const Token& t){ return t.GetValue() == TokenValue::GOTO; });
	if (gotoIter == provisional.cend()){
		return true;
	}
	
	if ((provisional.cend() - gotoIter) != 2){
		return false;
	}

	if (provisional.back().GetType() != TokenType::INTEGER){
		return false;
	}
	return true;
}
bool SyntaxAnalyser::IsValidOutcome(const std::vector<Token>& provisional){
	std::vector<Token>::const_iterator outcomePosIter = std::find_if(provisional.cbegin(), provisional.cend(), [](const Token& t){ return t.IsOutcome(); });
	if (outcomePosIter == provisional.cend())
		return true;
	else
		return ((provisional.cend() - outcomePosIter) == 1);
	
}

//TODO: Check lines which are too long
bool SyntaxAnalyser::IsValidIf(const std::vector<Token>& provisional){
	std::vector<Token>::const_iterator ifIter = std::find_if(provisional.cbegin(), provisional.cend(), [](const Token& t){ return t.GetValue() == TokenValue::IF; });
	if (ifIter == provisional.cend()){
		return true;
	}
	// Check if is first token in line
	if (provisional.cbegin() !=  ifIter){
		return false; 
	}
	// Check an action is present
	std::vector<Token>::const_iterator actionPosIter = std::find_if(ifIter, provisional.cend(), [](const Token& t){ return t.IsAction(); });
	if (actionPosIter == provisional.cend()){
		return false;
	}
	// Check if valid expression between IF and ACTION
	if (!IsExpression(std::vector<Token>(std::next(ifIter), actionPosIter))){
		return false;
	}

	return true;
}



void SyntaxAnalyser::PrintError(const ErrorCode& error){
	switch (error){
	case ErrorCode::EMPTY:
		std::cout << "Syntax Error : Empty lines are not allowed" << std::endl;
		break;
	case ErrorCode::DANGLING_BINARY:
		std::cout << "Syntax Error : Line may not begin or end with a binary operator" << std::endl;
		break;
	case ErrorCode::DANGLING_VARIABLE:
		std::cout << "Syntax Error : Line may not begin or end with a variable" << std::endl;
		break;
	case ErrorCode::INVALID_GOTO:
		std::cout << "Syntax Error: GOTO must be followed by a single integer" << std::endl;
		break;
	case ErrorCode::INVALID_OUTCOME:
		std::cout << "Syntax Error: BREAK, RANDOM, SILENCE may appear only at end of line" << std::endl;
		break;
	case ErrorCode::INVALID_IF:
		std::cout << "Syntax Error: Valid expression and action must follow IF keyword" << std::endl;
		break;
	case ErrorCode::INVALID_KEYWORD:
		std::cout << "Syntax Error: Unrecognised keyword" << std::endl;
		break;
	default:
		std::cout << "Syntax Error : Unclassified error reported" << std::endl;
		break;

	}
}
// IF EXPRESSION ACTION JUNK
//TODO: Refactor this class
//TODO: Need a token type for char variables and a token type for LASTOUTCOMES
//TODO: RValue does not detect last outcome slipping through the net

//TODO: Check all const