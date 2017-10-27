// Class: Strategy
// Description: Class to interpret strategies. Given a map to
// the variables in the language can return a selection to the
// prisoner game. Functions as a wrapper for Interpreter
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
	// Returns true if the code compiles and has not found an infinite loop
	inline bool IsValid() const { return m_interpreter.IsValid();};

	// Executes the code to get an action
	inline ActionType GetSelection()  { return m_interpreter.GetSelection(); }

	// Returns the code as a string
	inline std::string GetCode() const { return m_interpreter.GetCode(); }

	// Setters
	inline void SetValidStrategy(bool isValid) { m_interpreter.SetValidStrategy(isValid); }

private:
	Interpreter m_interpreter;
};

