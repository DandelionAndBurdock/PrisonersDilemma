#pragma once

#include "Prisoner.h"
#include "PrisonersDilemmaGame.h"
#include <cmath>

class Game
{
public:
	enum GameResult {PRISONER_A, PRISONER_B, DRAW, UNFINISHED};
public:
	struct Sentence{ //TODO: m_
		int punishmentSentence = 4;
		int temptationSentence = 0;
		int silentSentence = 2;
		int suckerSentence = 5;
	};
public:
	Game(Prisoner& prisonerA, Prisoner& prisonerB, int iterationsPerGame, Sentence& sentence);
	Game(Prisoner& prisonerA, Prisoner& prisonerB, int iterationsPerGame);
	~Game();

	GameResult GetWinner();
	bool IsFinished();
	void Resolve(ActionType choiceA, ActionType choiceB);

private:
	Prisoner& m_prisonerA;
	Prisoner& m_prisonerB;

	int m_iterations;
	int m_currentIteration;

	Sentence m_sentence;
	int m_maxSentence;

	// Helper function quickly returns maximum sentence

	// Returns absolute value of the score differenceget absolu
	inline int GetScoreDifference() { return abs(m_prisonerA.GetScore() - m_prisonerB.GetScore()); }
	inline int GetMaxScoreChange() { return (m_iterations - m_currentIteration) * m_maxSentence; }
};

//TODO: Don't include functions in class that are unrelated (make seperate functions for them) e.g. gcd in fraction class. 