#pragma once

class Gang;
#include "PrisonersDilemmaGame.h"

class GangGame
{
public:
	GangGame(Gang* gangA, Gang* gangB);
	~GangGame();

	//TODO: Implement: What kind of statistics?
	void PrintStatistics();

	void Run();

	int GetWinner(); 
private:
	Gang* m_gangA;
	Gang* m_gangB;

	void Resolve(ActionType choiceA, ActionType choiceB);

	int m_totalIterations;		// Maximum total number of iterations
	int m_currentIteration;		// Current iteration

	bool m_invalidStrategy;		// True if one strategy is detected to be invalid

	GangSentence m_sentence;

	const int m_draw = -1;
};
//TODO: Should inherit from common game class
