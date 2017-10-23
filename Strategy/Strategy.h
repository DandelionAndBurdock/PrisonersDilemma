// Class: Strategy
// Description: Class to interpret strategies. Given a map to
// the variables in the language can return a selection to the
// prisoner game
// Author: Philip Jones
// Date: 19/10/2017
#pragma once

#include "../PrisonerStrategyLanguage.h"
#include "../Interpreter/Interpreter.h"
#include "../Game/PrisonersDilemmaGame.h"

class Strategy
{
public:
	// Constructors
	Strategy(const std::string& filename, const IntMap& intVariables, const CharMap& charVariables);
	Strategy() {}
	
	// Destructor
	~Strategy();

	// Assignment operator
	Strategy& operator=(const Strategy& strategy);

	// Getters
	bool IsValid();
	ActionType GetSelection();
	std::string GetCode();

	// Setters
	void SetValidStrategy(bool isValid);

private:
	Interpreter m_interpreter;
};