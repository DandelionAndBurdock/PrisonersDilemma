// Class: Statement
// Description: A statement is an action. It can be 
// a whole line or part of a line.
// Author: Philip Jones
// Date: 14/10/2017
#pragma once

#include "Expression.h"
#include "../Game/PrisonersDilemmaGame.h" 
#include "../PrisonerStrategyLanguage.h"


class Statement{ 
public:
	// Evaluate statement and return an action
	virtual Action Execute(const IntMap& intVars, CharMap& charVars) = 0; 
	Statement(int linenumber) : m_linenumber(linenumber){}
	virtual ~Statement() {} 
	int m_linenumber; // Line number associated with this statement
};


class StatementIf : public Statement{
public:
	StatementIf(int lineNum, std::vector<Token> left, std::vector<Token> right, PSL::TokenValue relOp, Statement* action);
	~StatementIf();
	Action Execute(const IntMap& intVars, CharMap& charVars) override;

	Expression* m_left;		// Expression to the left of the relational operator in the IF statement 
	Expression* m_right;    // Expression to the right of the relational operator in the IF statement

	PSL::TokenValue m_relOp; // Relational operator
	Statement* m_action;	 // Statement to execute if condition evaluates to true (GOTO or an OUTCOME)
};

class StatementGoto : public Statement{
public:
	StatementGoto(int jumpLine);
	Action Execute(const IntMap& intVars, CharMap& charVars) override;

	int m_jumpLine;		// Line to jumpto
};

class StatementOutcome : public Statement{
public:
	StatementOutcome(int lineNum, TokenValue val);
	Action Execute(const IntMap& intVars, CharMap& charVars) override;

	TokenValue m_value;  //Type of outcome (BETRAY, SILENCE, RANDOM)
};
