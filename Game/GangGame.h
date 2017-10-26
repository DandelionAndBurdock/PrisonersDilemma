#pragma once

class Gang;
#include "PrisonersDilemmaGame.h"

class GangGame
{
public:
	GangGame(Gang* gangA, Gang* gangB, float spyProb = 0.0f, bool spiesActive = false, int numberIterations = 200);
	~GangGame();

	//TODO: Implement: What kind of statistics?
	void PrintStatistics();

	void Run();

	int GetWinner(); 
private:
	void CheckForSpies();
	bool ResolveSpies();
	Gang* m_gangA;
	Gang* m_gangB;

	void Resolve(ActionType choiceA, ActionType choiceB);

	int m_totalIterations;		// Maximum total number of iterations
	int m_currentIteration;		// Current iteration

	bool m_invalidStrategy;		// True if one strategy is detected to be invalid

	GangSentence m_sentence;

	bool m_spiesActive; // True if game is using spies

	const int m_draw = -1;

	float m_spyProb;
};
//TODO: Should inherit from common game class
