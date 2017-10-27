#include "Statement.h"

#include <iostream>
#include "../Utility/RandomNumberGenerator.h"
#include "../PrisonerStrategyLanguage.h"
#include "../Game/PrisonersDilemmaGame.h"

StatementIf::StatementIf(int lineNumber, std::vector<Token> left, std::vector<Token> right, TokenValue relOp, Statement* action) :
Statement(lineNumber), m_relOp(relOp), m_action(action){
	m_left = new Expression(left);
	m_right = new Expression(right);
}
StatementIf::~StatementIf(){
	delete m_left;
	delete m_right;
	delete m_action;
}

Action  StatementIf::Execute(const IntMap& intVars, CharMap& charVars){
	switch (m_relOp){
	case TokenValue::EQUAL_TO:
		if (m_left->Parse(intVars, charVars) == m_right->Parse(intVars, charVars)){
			return m_action->Execute(intVars, charVars);
		}
		else {
			return Action(ActionType::NEXT_LINE);
		}
	case TokenValue::LESS_THAN:
		if (m_left->Parse(intVars, charVars) > m_right->Parse(intVars, charVars)){
			return m_action->Execute(intVars, charVars);
		}
		else {
			return Action(ActionType::NEXT_LINE);
		}
	case TokenValue::GREATER_THAN:
		if (m_left->Parse(intVars, charVars) > m_right->Parse(intVars, charVars)){
			return m_action->Execute(intVars, charVars);
		}
		else {
			return Action(ActionType::NEXT_LINE);
		}
	default:
		std::cout << "Interpreter Error: Error interpreting IF statement" << std::endl;
	}
}
StatementGoto::StatementGoto(int jumpLine) :
Statement(0), m_jumpLine(jumpLine)
{}

Action StatementGoto::Execute(const IntMap& intVars, CharMap& charVars){
		return Action(ActionType::GOTO, m_jumpLine);
}

StatementOutcome::StatementOutcome(int lineNum, TokenValue val) :
	Statement(lineNum), m_value(val)
{}

Action StatementOutcome::Execute(const IntMap& intVars, CharMap& charVars){
	switch (m_value){
	case TokenValue::BETRAY:
		return Action(ActionType::BETRAY);
	case TokenValue::SILENCE:
		return Action(ActionType::SILENCE);
	case TokenValue::RANDOM:
		if (RNG->TrueOrFalse()) 
			return Action(ActionType::BETRAY);
		else
			return Action(ActionType::SILENCE);
	default:
		std::cout << "Interpreter Error: Error interpreting outcome statement" << std::endl;
	}
}
