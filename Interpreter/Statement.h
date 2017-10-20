// Class: Statement
// Description: Defines statements 
// Author: Philip Jones
// Date: 14/10/2017
#pragma once

#include "Expression.h"
#include "PrisonersDilemmaGame.h" //TODO: Fix include paths to be relative
//TODO: Consider typedef
class Statement{
public:
	virtual Action Execute(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars) = 0;
	Statement() = delete;
	virtual ~Statement() {} // TODO: Is this okay?
};


class StatementIf : public Statement{
	Action Execute(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars) override;

	Expression* left;
	Expression* right;

	TokenType relOp;
	Statement* m_action;
};

class StatementGoto : public Statement{
	Action Execute(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars) override;

	int line; 
};

class StatementOutcome : public Statement{
	Action Execute(const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars) override;

	TokenValue value;
};

//TODO: Add m_ prefix to this class