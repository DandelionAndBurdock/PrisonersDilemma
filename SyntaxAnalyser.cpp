#include "SyntaxAnalyser.h"

#include <algorithm> // For find_if(), count_if()
#include <iostream>
#include <vector>

#include "PrisonerStrategyLanguage.h"

SyntaxAnalyser::SyntaxAnalyser()
{
}


SyntaxAnalyser::~SyntaxAnalyser()
{
}

bool SyntaxAnalyser::IsArithmeticSubExpression(const std::vector<Token>& provisional) const{
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

bool SyntaxAnalyser::IsConditionalSubExpression(const std::vector<Token>& provisional) const{
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

bool SyntaxAnalyser::TestNonCharExpressionFormat(const std::vector<Token>& provisional) const { // Change name e.g. test non char format
	
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

bool SyntaxAnalyser::IsExpression(const std::vector<Token>& provisional) const
{
	if (TestCharExpressionFormat(provisional)){
		return true;
	}
	else{
		return TestNonCharExpressionFormat(provisional);
	}
}


bool SyntaxAnalyser::TestCharExpressionFormat(const std::vector<Token>& provisional) const{
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



bool SyntaxAnalyser::ValidateLine(const std::vector<Token>& provisional) const{
	if (IsEmptyLine(provisional)){
		PrintError(ErrorCode::EMPTY);
		return false;
	}
	// Can make a quick exit if line starts or ends with a binary operator
	if (IsDanglingBinaryOp(provisional)){
		PrintError(ErrorCode::DANGLING_BINARY);
		return false;
	}

	// Can make a quick exit if line begins with rValue or ends with a variable
	if (IsDanglingVariable(provisional)){
		PrintError(ErrorCode::DANGLING_VARIABLE);
		return false;
	}

	for (auto iter = provisional.begin(); iter != provisional.end(); ++iter){
		switch (iter->GetValue()){
		case TokenValue::GOTO:
			if (!IsValidGOTO(std::vector<Token>(iter, provisional.end()))){
				PrintError(ErrorCode::DANGLING_VARIABLE);
				return false;
			}
			break;
		case TokenValue::BETRAY: // Rule 2: OUTCOMES should not be followed by anything
		case TokenValue::RANDOM:
		case TokenValue::SILENCE:
			if (!IsValidOutcome((std::vector<Token>(iter, provisional.end())))){ // IF TokenType:: == OUTCOME && 
				PrintError(ErrorCode::INVALID_OUTCOME);
				return false;
			}
			break;
		case TokenValue::IF:

			if (!IsValidIf((std::vector<Token>(iter, provisional.end())))){ // IF TokenType:: == OUTCOME && 
				PrintError(ErrorCode::INVALID_IF);
				return false;
			}
			break;
		}

		return true;
	}
}


bool SyntaxAnalyser::IsEmptyLine(const std::vector<Token>& provisional) const{
	return provisional.empty();
}
bool SyntaxAnalyser::IsDanglingBinaryOp(const std::vector<Token>& provisional) const {
	return (provisional.cbegin()->IsBinOp() || provisional.rbegin()->IsBinOp());
}
bool SyntaxAnalyser::IsDanglingVariable(const std::vector<Token>& provisional) const {
	return (provisional.cbegin()->IsRValue() || provisional.rbegin()->IsVariable());
}
bool SyntaxAnalyser::IsValidGOTO(const std::vector<Token>& provisional) const{
	if (provisional.size() != 2){
		return false;
	}
	if (provisional.back().GetType() != TokenType::INTEGER){
		return false;
	}
	return true;
}
bool SyntaxAnalyser::IsValidOutcome(const std::vector<Token>& provisional) const{
	return (provisional.size() == 1);
}
bool SyntaxAnalyser::IsValidIf(const std::vector<Token>& provisional) const{
	// Check an action is present
	std::vector<Token>::const_iterator actionPosIter = std::find_if(provisional.cbegin(), provisional.cend(), [](const Token& t){ return t.IsAction(); });
	if (actionPosIter == provisional.cend()){
		return false;
	}
	// Check if valid expression between IF and ACTION
	if (!IsExpression(std::vector<Token>(std::next(provisional.cbegin()), actionPosIter))){
		return false;
	}

	return true;
}



void SyntaxAnalyser::PrintError(const ErrorCode& error) const{
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