// Class: Prisoner
// Description: 
// Author: Philip Jones
// Date: 19/10/2017
#pragma once

#include "../Strategy/Strategy.h"
#include "PrisonersDilemmaGame.h"
#include "../PrisonerStrategyLanguage.h"
class Prisoner
{
protected:
	//TODO: Why can't make const?
	const char outcomes[4] = { 'W', 'X', 'Y', 'Z' };			// 
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
	inline int  GetScore() { return m_score; }
	inline int  GetID()    { return m_ID; }

	// Returns true if strategy code compiled and has not stuck in an infinite loop
	bool HasValidStrategy();
	// Returns strategy code used by the interpreter 
	std::string GetCode();

	// Setters
	inline void AddToScore(int x) { m_score += x; }

	void SetLastOutcome(char outcome);
	void SetValidStrategy(bool isValid);

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


class GangPrisoner : public Prisoner {
protected:
	const char gangOutcomes[3] = { 'A', 'B', 'C' }; //TODO: Remove Magic Number

public:
	GangPrisoner(int ID, const std::string& strategy);//TODO: Strategy file path

protected:
	//TOOD: Should be capital o
	int m_alloutcomesA;	  // TODO: Comment
	int m_alloutcomesB;
	int m_alloutcomesC;

	void Reset() override;

	IntMap  MakeIntegerVariableMap() override;
	CharMap MakeCharVariableMap()    override;

};

