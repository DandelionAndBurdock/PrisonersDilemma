// Class: Game
// Description: Simulates a game of prisoners dilemma between two prisoners 
// Author: Philip Jones
// Date: 19/10/2017
#pragma once

#include "Prisoner.h"
#include "PrisonersDilemmaGame.h"

class Game
{

public:
	// Constructors
	Game(Prisoner& prisonerA, Prisoner& prisonerB, int iterationsPerGame, Sentence& sentence);
	Game(Prisoner& prisonerA, Prisoner& prisonerB, int iterationsPerGame);
	// Destructor
	~Game();

	//  and returns the ID of the winning prisoner or
	// a negative number if the game is drawn
	int GetWinner();
	// Simulates the game between prisoner A and prisoner B
	void Run();

private:
	
	Prisoner& m_prisonerA;		// First competing prisoner
	Prisoner& m_prisonerB;		// Second competing prisoner

	int m_totalIterations;		// Maximum total number of iterations
	int m_currentIteration;		// Current iteration

	Sentence m_sentence;		// Data for score changes 
	int m_maxSentence;			// Largest change of score possible in one round 

	bool m_invalidStrategy;		// True if one strategy is detected to be invalid

	const int m_draw = -1;		// Negative number signifies draw

	// Updates prisoner data after one round of the game
	void Resolve(ActionType choiceA, ActionType choiceB);
	

	// Returns true if a prisoner can no longer lose with the iterations 
	// remaining or has an invalid strategy (and so automatically loses)
	bool IsFinished();
};