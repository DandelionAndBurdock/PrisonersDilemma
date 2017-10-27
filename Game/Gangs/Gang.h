
#pragma once

#include "../PrisonersDilemmaGame.h"

#include <vector>



class Prisoner;

class Gang
{
public:
	// Constructors
	// Generates gangSize prisoners with random strategies
	Gang(int ID, int gangSize, bool leaderChange = false);	
	// For each file in filepath adds a prisoner using the strategy at that path
	Gang(int ID, const std::vector<std::string>& filePaths);	
	// For each file in filepath adds a prisoner using the strategy at that path. 
	// leaderChange specifies if the leader sticks or changes intial spy guess
	Gang(int ID, const std::vector<std::string>& filePaths, bool leaderChange);
	
	// Copy Constructor
	Gang(const Gang& gang);
	// Destructor
	~Gang();

	// Polls each prisoner to get his/her selection and updates gang state based on their response
	void GetVotes();

	// Sets all game related variables to default values
	void Reset();

	// Calculates if this gang has a spy or not for this iteration
	bool PlantSpy(float m_prob); 

	// Spy returns minority vote. If votes are tied spy runs own strategy
	ActionType GetSpyVote();

	// Leader will attempt to find the spy by extension of Monty Hall Paradox
	bool FindSpy();

	// Create gangSize members with randomly generated strategies
	void GenerateNewMembers(int gangSize); 
	
	// Create a gang member for each file in filepath 
	void LoadMembers(std::vector<std::string> filepaths); 

	// Getters 
	// Get majority decision of gang in this iteration
	inline ActionType GetDecision() const { return m_decision; }
	// Returns true if gang did not vote unanimously
	inline bool IsMixed() const { return m_mixedResponse; }
	// Returns the number of the gang who voted for betray
	inline int GetNumBetray() const { return m_numBetrays; }
	// Returns the number of the gang who voted for silence
	inline int GetNumSilence() const { return m_numSilence; }
	// Returns ID of the gang
	inline int GetID() const { return m_ID; }
	// Returns the score for the current game
	inline int GetScore() const { return m_score; }
	// Returns strategy used by the gang as a string
	std::string GetCode(); 
	// Returns true if the leader found the spy
	inline bool DidFindSpy()const { return m_foundSpy; }
	// Returns the leader behaviour: If true leader does not stick with original decision
	inline bool LeaderChanges() const { return m_leaderChange; }
	// Returns true if a spy is present in the gang
	inline bool HasSpy() const { return m_hasSpy; }
	// Returns true if the gang has a valid strategy
	inline bool HasValidStrategy() const { return m_validStrategy; }
	// Setters 
	void SetLastOutcome(char outcome);
	inline void SetLeaderChange(bool change) { m_leaderChange = change; }
	inline void SetValid(bool valid) { m_validStrategy = valid; }
	// Modify the score by x
	void AddToScore(int x);


private:
	int					   m_ID;			 // Identification number for this gang //TODO: Make unique
	std::vector<Prisoner*> m_prisoners;		// Vector of prisoners in the gang
	int					   m_gangSize;		 // Number of prisoners in the gang
	bool				   m_validStrategy; // Returns true if gang holds a valid strategy

	bool m_mixedResponse; // True if gang did not reach consensus
	int m_numBetrays;	  // Number of gang members that chose betray in the last iteration
	int m_numSilence;	  // Number of gang members that chose silence in the last iteration

	int m_score;		 // Current score in this game

	ActionType m_decision; // Majority decision made by the gang

	bool m_hasSpy;		// True if gang has a spy
	int m_spyIndex;		// Identifies prisoner randomly selected as spy (if present)
	int m_leaderIndex; // Identifies prsioner randomly delegated leader (can not be spy)
	bool m_leaderChange;	// True if leader always changes spy pick false if leader never changes spy pick
	bool m_foundSpy;	// True if discovered a spy in this gang
	
	std::vector<std::string> m_filePaths; // File paths used by gang

	std::string m_directory;
};



