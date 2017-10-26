#pragma once

#include "PrisonersDilemmaGame.h"

#include <vector>



class Prisoner;

class Gang
{
public:
	// If given only an ID will generate a new gang
	Gang(int ID, int gangSize);
	Gang(int ID, const std::vector<std::string>& filePaths);
	Gang(int ID, const std::vector<std::string>& filePaths, bool leaderChange);
	~Gang();

	// Polls each prisoner to get his/her selection and updates gang state based on their response
	void GetVotes();

	void Reset();

	// Calculates if this gang has a spy or not
	bool PlantSpy(float m_prob); 
	ActionType GetSpyVote();

	// Getters TODO: const
	inline ActionType GetDecision() { return m_decision; }
	inline bool IsMixed() { return m_mixedResponse; }
	inline int GetNumBetray(){ return m_numBetrays; }
	inline int GetNumSilence() { return m_numSilence; }
	inline int GetID() { return m_ID; }
	inline int GetScore() { return m_score; }
	std::string GetCode();
	inline bool DidFindSpy() { return m_foundSpy; }
	inline bool LeaderChanges() { return m_leaderChange; }
	inline bool HasSpy() { return m_hasSpy; }
	// Setters 
	void SetLastOutcome(char outcome);
	void AddToScore(int x);
	inline void SetLeaderChange(bool change) { m_leaderChange = change; }
	bool FindSpy();

private:
	int					   m_ID;			 // Identification number for this gang //TODO: Make unique
	std::vector<Prisoner*> m_prisoners;		// Vector of prisoners in the gang
	int					   m_gangSize;		 // Number of prisoners in the gang


	bool m_mixedResponse; // True if gang did not reach consensus
	int m_numBetrays;	  // Number of gang members that chose betray in the last iteration
	int m_numSilence;	  // Number of gang members that chose silence in the last iteration

	int m_score;

	ActionType m_decision;

	
	bool m_hasSpy;		// True if gang has a spy
	int m_spyIndex;		// 
	int m_leaderIndex;
	bool m_leaderChange;	// True if leader always changes false if leader never changes spy pick
	bool m_foundSpy;	// True if discovered a spy in this gang
	


	std::vector<std::string> m_filePaths;

	void GenerateNewMembers(int gangSize);
	void LoadMembers(std::vector<std::string> filepaths);

	std::string m_directory;
};



