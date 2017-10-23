// Class: Strategy
// Description: Class to interpret strategies. Given a map to
// the variables in the language can return a selection to the
// prisoner game
// Author: Philip Jones
// Date: 19/10/2017
#pragma once

#include <map> //TODO: Forward declaration?
#include "../PrisonerStrategyLanguage.h"
#include "../Interpreter/Interpreter.h"
#include "PrisonersDilemmaGame.h"

class Strategy
{
public:
	Strategy(const std::string& filename, const IntMap& intVariables, const CharMap& charVariables);
	Strategy() {}
	~Strategy();
	Strategy& operator=(const Strategy& strategy);
	bool IsValid();
	void SetValidStrategy(bool isValid);
	ActionType GetSelection(); 
	std::string GetCode();

private:
	Interpreter m_interpreter;
};