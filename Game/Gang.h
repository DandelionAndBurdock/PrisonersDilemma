#pragma once

#include "PrisonersDilemmaGame.h"

#include <vector>

class Prisoner;

class Gang
{
public:
	Gang(int ID, const std::vector<Prisoner*>& prisoners);
	~Gang();

	void GetVotes();

private:
	int					   m_ID;			 // Identification number for this gang //TODO: Make unique
	std::vector<Prisoner*> m_prisoners;		// Vector of prisoners in the gang
	int					   m_gangSize;		 // Number of prisoners in the gang

	bool m_mixedResponse; // True if gang did not reach consensus
	int m_numBetrays;	  // Number of gang members that chose betray in the last iteration
	int m_numSilence;	  // Number of gang members that chose silence in the last iteration
};

