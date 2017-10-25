#include "Gang.h"

#include "Prisoner.h"
#include "../Utility/RandomNumberGenerator.h"


Gang::Gang(int ID, int gangSize) :
m_ID(ID)
{
	GenerateNewMembers();
}
Gang::Gang(int ID, std::vector<std::string> filePaths) :
	m_ID(ID) 
{
	LoadMembers(filePaths);
}


void Gang::GenerateNewMembers() {
	return; //TODO: Implement necessary changes to the strategy generator
}
void Gang::LoadMembers(std::vector<std::string> filepaths) {
	for (int i = 0; i < filepaths.size(); ++i) {
		m_prisoners.push_back(new GangPrisoner(i, filepaths[i]));
	}
	m_gangSize = filepaths.size();
}

Gang::~Gang()
{
	//for (Prisoner* ptr : m_prisoners) {
	//	delete ptr;
	//}
}

void Gang::GetVotes() {
	
	std::vector<ActionType> votes;
	for (Prisoner* &prisoner : m_prisoners) {
		votes.push_back(prisoner->GetSelection());
	}
	m_numBetrays = std::count(votes.begin(), votes.end(), ActionType::BETRAY);
	m_numSilence = std::count(votes.begin(), votes.end(), ActionType::SILENCE);
	if (m_numBetrays != m_numSilence) {
		m_mixedResponse = true;
		if (m_numBetrays > m_numSilence) {
			m_decision = ActionType::BETRAY;
		}
		else {
			m_decision = ActionType::SILENCE;
		}
	}
	else {
		m_mixedResponse = false;
	}

}


//TODO: Can use reset in constructor (also of prisoner)
void Gang::Reset() {
	m_numBetrays = 0;
	m_numSilence = 0;
	m_score = 0;
	m_decision = ActionType::INVALID_ACTION;
	m_mixedResponse = false;
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