#include "Statement.h"

#include <iostream>
#include "RandomNumberGenerator.h"


//TODO: Use a typedef for Selection 
Action  StatementIf::Execute(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars){
	switch (relOp){
	case TokenValue::EQUAL_TO:
		if (left->Parse(intVars, charVars) == right->Parse(intVars, charVars)){
			return m_action->Execute(intVars, charVars);
		}
		break;
	case TokenValue::LESS_THAN:
		if (left->Parse(intVars, charVars) > right->Parse(intVars, charVars)){
			return m_action->Execute(intVars, charVars);
		}
		break;
	case TokenValue::GREATER_THAN:
		if (left->Parse(intVars, charVars) > right->Parse(intVars, charVars)){
			return m_action->Execute(intVars, charVars);
		}
		break;
	default:
		std::cout << "Interpreter Error: Error interpreting IF statement" << std::endl;
	}
}

Action StatementGoto::Execute(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars){
		return Action(ActionType::GOTO, line);
}

Action StatementOutcome::Execute(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars){
	switch (value){
	case TokenValue::BETRAY:
		return Action(ActionType::BETRAY);
	case TokenValue::SILENCE:
		return Action(ActionType::SILENCE);
	case TokenValue::RANDOM:
		if (RandomNumberGenerator::Instance()->GetRandInt(0, 1) % 2) //TODO: Check
			return Action(ActionType::BETRAY);
		else
			return Action(ActionType::SILENCE);
	default:
		std::cout << "Interpreter Error: Error interpreting outcome statement" << std::endl;
	}
}
//TODO: Urgent use RNG