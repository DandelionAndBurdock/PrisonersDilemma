// Class: Statement
// Description: A statement is an action. It can be 
// a whole line or part of a line.
// Author: Philip Jones
// Date: 14/10/2017
#pragma once

#include "Expression.h"
#include "../Game/PrisonersDilemmaGame.h" //TODO: Fix include paths to be relative
#include "../PrisonerStrategyLanguage.h"
//TODO: Consider typedef
class Statement{ //TODO: Access specifier
public:
	virtual Action Execute(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars) = 0;
	Statement(int linenumber) : m_linenumber(linenumber){}
	virtual ~Statement() {} // TODO: Is this okay?
	int m_linenumber;
};


class StatementIf : public Statement{
public:
	StatementIf(int lineNum, std::vector<Token> left, std::vector<Token> right, PSL::TokenValue relOp, Statement* action);
	~StatementIf();
	Action Execute(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars) override;

	Expression* m_left;
	Expression* m_right;

	PSL::TokenValue m_relOp;
	Statement* m_action;
};

class StatementGoto : public Statement{
public:
	StatementGoto(int jumpLine);
	Action Execute(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars) override;

	int m_jumpLine; 
};

class StatementOutcome : public Statement{
public:
	StatementOutcome(int lineNum, TokenValue val);
	Action Execute(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars) override;

	TokenValue m_value;
};

//TODO: Add m_ prefix to this class
//TODO: Check variable alignment