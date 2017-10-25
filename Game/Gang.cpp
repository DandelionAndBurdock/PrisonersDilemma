#include "Gang.h"

#include "Prisoner.h"
#include "../Utility/RandomNumberGenerator.h"
Gang::Gang(int ID, const std::vector<Prisoner*>& prisoners)
{

}


Gang::~Gang()
{
}

void Gang::GetVotes() {
	
	std::vector<ActionType> votes;
	for (Prisoner* &prisoner : m_prisoners) {
		votes.push_back(prisoner->GetSelection());
	}
	int m_numBetrays = std::count(votes.begin(), votes.end(), ActionType::BETRAY);
	int m_numSilence = std::count(votes.begin(), votes.end(), ActionType::SILENCE);
	if (m_numBetrays != m_numSilence) {
		m_mixedResponse = true;
	}
	else {
		m_mixedResponse = false;
	}

}