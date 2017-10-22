// Class: Prisoner
// Description: 
// Author: Philip Jones
// Date: 19/10/2017
#pragma once

#include "Strategy.h"
#include "PrisonersDilemmaGame.h"
#include "../PrisonerStrategyLanguage.h"
class Prisoner
{
private:
	static char outcomes[];  //TODO: Static, make const
public:
	Prisoner(int ID, const std::string& strategy); //TODO:Faster to pass const?
	Prisoner(const Prisoner& prisoner);


	~Prisoner();

	ActionType MakeSelection();

	inline int  GetScore() { return m_score; }
	inline void AddToScore(int x) { m_score += x; }

	inline int GetID() { return m_ID; }

	void SetLastOutcome(char outcome);

	bool HasValidStrategy();

	void ChangeStrategy(const std::string& strategy);

	void Reset();

	void PrintDebugInfo();
private:
	char  m_lastOutcome; // TODO: Comment
	int      m_alloutcomesW;
	int      m_alloutcomesX;
	int      m_alloutcomesY;
	int      m_alloutcomesZ;
		 
	int      m_iterations;
	int		 m_score;
	int		 m_ID;

	const std::map<TokenValue, int*>  m_intVars;
	const std::map<TokenValue, char*> m_charVars;
	Strategy m_strategy;

	//
	std::map<TokenValue, int*> MakeIntegerVariableMap();
	std::map<TokenValue, char*> MakeCharVariableMap(); //TODO: Should it be a char or an Outcome???


};

//TODO: What should m_lastOutcome be initialised too

