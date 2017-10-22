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
	const std::vector<char> Outcomes{ 'W', 'X', 'Y', 'Z' }; //TODO: Remove
public:
	Prisoner(const std::string& strategy); //TODO:Faster to pass const?
	~Prisoner();

	ActionType MakeSelection();

	inline int  GetScore() { return m_score; }
	inline void AddToScore(int x) { m_score += x; }

	inline void SetLastOutcome(char outcome) {	m_lastOutcome = outcome; }
private:
	Strategy m_strategy;
		
	char  m_lastOutcome; // TODO: Comment
	int      m_alloutcomesW;
	int      m_alloutcomesX;
	int      m_alloutcomesY;
	int      m_alloutcomesZ;
		 
	int      m_iterations;
	int		 m_score;

	//
	std::map<TokenValue, int*> MakeIntegerVariableMap();
	std::map<TokenValue, char*> MakeCharVariableMap(); //TODO: Should it be a char or an Outcome???
};

//TODO: What should m_lastOutcome be initialised too

