// Class: Gang
// Description: Gang manages a group of prisoners who may 
// contain a spy and leader
// Author: Philip Jones
// Date: 21/10/2017
#include "Gang.h"

#include "GangPrisoner.h"
#include "../../Utility/RandomNumberGenerator.h"
#include "../../Strategy/StrategyGenerator.h"
#include "../../Strategy/StrategyTester.h"

Gang::Gang(int ID, int gangSize, bool leaderChange) :
m_ID(ID), m_leaderChange(false)
{
	m_gangSize = gangSize;
	m_directory = "GangTournaments//";
	GenerateNewMembers(gangSize);
	Reset();


}
Gang::Gang(int ID, const std::vector<std::string>& filePaths) :
	m_ID(ID), m_filePaths(filePaths), m_leaderChange(false)
{
	LoadMembers(filePaths);
	Reset();

	m_directory = "GangTournaments//";
}

Gang::Gang(int ID, const std::vector<std::string>& filePaths, bool leaderChange) :
Gang(ID, filePaths)
{
	m_leaderChange = leaderChange;
}


void Gang::GenerateNewMembers(int gangSize) {
	StrategyGenerator generator(true, true);
	StrategyTester tester;
	for (int i = 0; i < gangSize; ++i) {
		std::string strategyFile = m_directory + std::to_string(m_ID) + "-" + std::to_string(i) + fileFormat;
		generator.GenerateStrategy(strategyFile);
		m_prisoners.push_back(new GangPrisoner(i, strategyFile));
	}
}
void Gang::LoadMembers(std::vector<std::string> filepaths) {
	for (int i = 0; i < filepaths.size(); ++i) {
		m_prisoners.push_back(new GangPrisoner(i, filepaths[i]));
	}
	m_gangSize = filepaths.size();
}

Gang::~Gang()
{
}

void Gang::GetVotes() {
	
	std::vector<ActionType> votes;
	for (int i = 0; i < m_prisoners.size(); ++i) {
		if (m_spyIndex == i) {
			continue;
		}
		votes.push_back(m_prisoners[i]->GetSelection());
	}
	if (std::count(votes.begin(), votes.end(), ActionType::INVALID_ACTION)) {
		SetValid(false);
		return;
	}

	m_numBetrays = std::count(votes.begin(), votes.end(), ActionType::BETRAY);
	m_numSilence = std::count(votes.begin(), votes.end(), ActionType::SILENCE);

	if (m_hasSpy) {
		votes.push_back(GetSpyVote());
	}

	m_numBetrays = std::count(votes.begin(), votes.end(), ActionType::BETRAY);
	m_numSilence = std::count(votes.begin(), votes.end(), ActionType::SILENCE);

	m_mixedResponse = (m_numBetrays != m_numSilence);
	if (m_numBetrays > m_numSilence) {
		m_decision = ActionType::BETRAY;
	}
	else {
		m_decision = ActionType::SILENCE;
	}
}

void Gang::Reset() {
	m_numBetrays = 0;
	m_numSilence = 0;
	m_score = 0;
	m_decision = ActionType::INVALID_ACTION;
	m_mixedResponse = false;
	m_hasSpy = false;
	m_spyIndex = -1;
	m_leaderIndex = -1;
}


void Gang::SetLastOutcome(char outcome) {
	for (Prisoner* &prisoner : m_prisoners) {
		prisoner->SetLastOutcome(outcome);
	}
}
void Gang::AddToScore(int x) {
	m_score += x;
	for (Prisoner* &prisoner : m_prisoners) {
		prisoner->AddToScore(x);
	}
}

std::string Gang::GetCode() {
	std::string code = std::string();
	int i = 0;
	for (Prisoner* &prisoner : m_prisoners) {
		code += std::string("**********Prisoner ") + std::to_string(++i) + "*************\n"; //TODO: Ugly
		code += prisoner->GetCode();
		code += '\n';
	}
	return code;
}

bool Gang::PlantSpy(float m_prob) {
	m_hasSpy = (RNG->GetRandFloat() < m_prob);
	if (m_hasSpy) {
		m_spyIndex = RNG->GetRandInt(0, m_gangSize - 1);
		m_leaderIndex = RNG->GetRandInt(0, m_gangSize - 1);
	}
	return m_hasSpy;
}

ActionType Gang::GetSpyVote() {
	if (m_numBetrays > m_numSilence) {
		return SILENCE;
	}
	else if (m_numSilence > m_numBetrays) {
		return BETRAY;
	}
	else {
		return m_prisoners[m_spyIndex]->GetSelection();
	}
}

//TODO: Refactor -> Split into initial and final guess functions
bool Gang::FindSpy() {
	if (!m_hasSpy) {
		m_foundSpy = false;
		return false;
	}
		
	// Guess a spy at random (not the leader)
	int initalGuess = RNG->GetExcludedRandInt(0, m_gangSize - 1, m_leaderIndex);

	// Reveal non-spy (other than the leader)
	std::vector<int> remainingIndices; //TODO: This method will not be efficient for large gang sizes
	for (int i = 0; i < m_gangSize; ++i) {
		if (i != m_spyIndex && i != m_leaderIndex && i != initalGuess) {
			remainingIndices.push_back(i);
		}
	}

	int innocentIndex = remainingIndices[RNG->GetRandInt(0, remainingIndices.size() -1)];
	

	// Depending on leader characteristics stick with original guess or try a new one
	int finalGuess;
	if (m_leaderChange) {
		remainingIndices.clear();
		for (int i = 0; i < m_gangSize; ++i) {
			if (i != innocentIndex && i != m_leaderIndex && i != initalGuess) {
				remainingIndices.push_back(i);
			}
		}
		finalGuess = remainingIndices[RNG->GetRandInt(0, remainingIndices.size() - 1)];
	}
	else {
		finalGuess = initalGuess;
	}

	m_foundSpy = (finalGuess == m_spyIndex);
	return m_foundSpy;
}