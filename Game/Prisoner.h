// Class: Prisoner
// Description: 
// Author: Philip Jones
// Date: 19/10/2017
#pragma once

#include "../Strategy/Strategy.h"
#include "PrisonersDilemmaGame.h"
#include "../PrisonerStrategyLanguage.h"

#include <mutex>

class Prisoner
{
protected:
	// Possible outcomes of one round for a prisoner
	const char outcomes[4] = { 'W', 'X', 'Y', 'Z' }; // W - Both silent, X - Betrayed, Y - Betrays, Z - Both betray
public:
	// Constructor
	Prisoner(int ID, const std::string& strategy); 
	// Copy constructor
	Prisoner(const Prisoner& prisoner);
	// Assignment operator
	Prisoner& operator=(const Prisoner& prisoner);
	// Destructor
	~Prisoner();

	// Interprets strategy code to return a selection
	virtual ActionType GetSelection();

	// Getters 
	inline int  GetScore() const { return m_score; }
	inline int  GetID()    const { return m_ID; }

	// Returns true if strategy code for prisoner ID has compiled and has not stuck in an infinite loop
	static bool HasValidStrategy(int ID);
	// Sets valid strategy for prisoner with ID
	static void SetValidStrategy(int ID, bool isValid);
	// Holds a map from prisoner ID to valid strategy status
	static std::map<int, bool> m_validStrategies; 
	// Lock for valid strategies map
	static std::mutex m_validStrategyLock;
	// Returns strategy code used by the interpreter 
	std::string GetCode();

	// Setters
	inline void AddToScore(int x) { m_score += x; }
	void SetLastOutcome(char outcome);
	
	// Load new strategy at filepath
	void ChangeStrategy(const std::string& filepath);

	// Set all game variables to zero
	virtual void Reset();

protected:
	Prisoner(int ID) : m_ID(ID) {}

	char m_lastOutcome;		// Holds outcome of the last game (W, X, Y, Z)
	int  m_alloutcomesW;	// Running total of W outcomes in current game 
	int  m_alloutcomesX;	// Running total of X outcomes in current game
	int  m_alloutcomesY;  	// Running total of Y outcomes in current game
	int  m_alloutcomesZ;	// Running total of Z outcomes in current game
		 
	int  m_iterations;		// Current number of iterations in this game
	int	 m_score;			// Cumulative total of years sentenced
	int	 m_ID;				// Prisoner identifier //TODO: Make unique?

	IntMap  m_intVars;		// Map from integer variables to pointers
	CharMap m_charVars;		// Map from character variables to pointers
	
	Strategy m_strategy;	// Current strategy applied by the prisoner //TODO: Right now is order dependent

	virtual IntMap  MakeIntegerVariableMap();
	virtual CharMap MakeCharVariableMap(); //TODO: Should it be a char or an Outcome???
};



