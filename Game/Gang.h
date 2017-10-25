#pragma once

#include "PrisonersDilemmaGame.h"

#include <vector>

class Prisoner;

class Gang
{
public:
	// If given only an ID will generate a new gang
	Gang(int ID, int gangSize);//TODO: take in number of iterations
	Gang(int ID, std::vector<std::string> filePaths);//TODO: take in number of iterations
	~Gang();

	// Polls each prisoner to get his/her selection and updates gang state based on their response
	void GetVotes();

	void Reset();

	inline ActionType GetDecision() { return m_decision; }
	inline bool IsMixed() { return m_mixedResponse; }
	inline int GetNumBetray(){ return m_numBetrays; }
	inline int GetNumSilence() { return m_numSilence; }
	inline int GetID() { return m_ID; }
	inline int GetScore() { return m_score; }
	// Setters
	void SetLastOutcome(char outcome);
	void AddToScore(int x);

private:
	int					   m_ID;			 // Identification number for this gang //TODO: Make unique
	std::vector<Prisoner*> m_prisoners;		// Vector of prisoners in the gang
	int					   m_gangSize;		 // Number of prisoners in the gang

	bool m_mixedResponse; // True if gang did not reach consensus
	int m_numBetrays;	  // Number of gang members that chose betray in the last iteration
	int m_numSilence;	  // Number of gang members that chose silence in the last iteration

	int m_score;

	ActionType m_decision;


	void GenerateNewMembers();
	void LoadMembers(std::vector<std::string> filepaths);
};



