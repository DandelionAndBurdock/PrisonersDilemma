// Class: Strategy
// Description: Class to interpret strategies. Given a map to
// the variables in the language can return a selection to the
// prisoner game
// Author: Philip Jones
// Date: 19/10/2017
#pragma once

#include <map> //TODO: Forward declaration?
//TODO: Think this structure is okay because prisoner shouldn't really know how a strategy is interpreted + extension e.g???

#include "../PrisonerStrategyLanguage.h"
#include "../Interpreter/Interpreter.h"
#include "PrisonersDilemmaGame.h"

class Strategy
{
public:
	Strategy(const std::string& filename, const std::map<TokenValue, int*>& intVariables, const std::map<TokenValue, char*>& charVariables);
	Strategy() {}
	~Strategy();
	Strategy& operator=(const Strategy& strategy);
	bool IsValid();
	ActionType GetAction(); //TODO: Fix selection/action flip-flopping
	std::string GetCode();

private:
	Interpreter m_interpreter;
};
//TODO: Check consistent use of m_ prefix
//TODO: Inconsistent use of selection and outcome