#pragma once

class Gang;
#include "../PrisonersDilemmaGame.h"

class GangGame
{
public:
	GangGame(Gang* gangA, Gang* gangB, float spyProb = 0.0f, bool spiesActive = false, int numberIterations = 200);
	~GangGame();

	// Print statistics about the game
	void PrintStatistics() const;

	// Simulate a game between gangA and gangB
	void Run();

	// Return the winner of the game or a negative number if drawn
	int GetWinner(); 

	// Return number of times a spy was present but not detected
	inline int GetSpyMisses() const { return m_spyPresentNotFound; }
	// Return number of times a spy was present and detected by a leader who changed initial guess
	inline int GetSpyChange() const { return m_spyFoundLeaderChange; }
	// Return number of times a spy was present and detected by a leader who stuck to initial guess
	inline int GetSpyStick() const  { return m_spyFoundLeaderStick; }

private:
	// Two gangs participating in the game
	Gang* m_gangA;
	Gang* m_gangB;

	// Leaders of gang A and gang B try to discover if spy is present
	void CheckForSpies();

	// Modify score according to the rules of the spy game
	bool ResolveSpies();

	// Modify score according to the rules of the prisoner dilemma game
	void Resolve(ActionType choiceA, ActionType choiceB);

	// Returns true if the game is over
	bool IsFinished();

	int m_totalIterations;		// Maximum total number of iterations
	int m_currentIteration;		// Current iteration
	bool m_spiesActive;			// True if game is using spies
	bool m_invalidStrategy;		// True if one strategy is detected to be invalid

	GangSentence m_sentence;   // Contains paramaters for modifying prisoner score



	const int m_draw = -1; // Returned if game is drawn

	float m_spyProb;     // Probability for a spy to be present on a given iteration

	// Helper functions for modifying scores based on outcome of spy game
	void BothFindSpy();  
	void GangAFindSpy(); 
	void GangBFindSpy();
	void NoSpyFound();

	int m_spyPresentNotFound = 0;     // number of times a spy was present but not detected
	int m_spyFoundLeaderChange = 0;   // number of times a spy was present and detected by a leader who changed initial guess
	int m_spyFoundLeaderStick = 0;    // number of times a spy was present and detected by a leader who stuck to initial guess

	// Helper functions for updating scores
	void ResolveWW();
	void ResolveXY();
	void ResolveYX();
	void ResolveZZ();
	void ResolveAB();
	void ResolveBA();
	void ResolveCC();
};

