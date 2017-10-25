#include "GangGame.h"

#include "Gang.h"

GangGame::GangGame(Gang* gangA, Gang* gangB, float spyProb, bool spiesActive) :
	m_gangA(gangA), m_gangB(gangB), m_spyProb(spyProb), m_spiesActive(spiesActive)
	
{
	// Ensure gangs start clean
	m_gangA->Reset();
	m_gangB->Reset();




	m_totalIterations = 200;
}	 


GangGame::~GangGame()
{
}


void GangGame::Resolve(ActionType choiceA, ActionType choiceB) {

	if (!m_gangA->IsMixed() && !m_gangB->IsMixed()) {

		if (choiceA == SILENCE && choiceB == SILENCE) {
			m_gangA->SetLastOutcome('W');
			m_gangB->SetLastOutcome('W');
			m_gangA->AddToScore(m_sentence.m_silent);	 
			m_gangB->AddToScore(m_sentence.m_silent);   
		}
		else if (choiceA == SILENCE && choiceB == BETRAY) {
			m_gangA->SetLastOutcome('X');
			m_gangB->SetLastOutcome('Y');
			m_gangA->AddToScore(m_sentence.m_sucker);
			m_gangB->AddToScore(m_sentence.m_temptation);
		}
		else if (choiceA == BETRAY && choiceB == SILENCE) {
			m_gangA->SetLastOutcome('Y');
			m_gangB->SetLastOutcome('X');
			m_gangA->AddToScore(m_sentence.m_temptation);
			m_gangB->AddToScore(m_sentence.m_sucker);
		}
		else if (choiceA == BETRAY && choiceB == BETRAY) {
			m_gangA->SetLastOutcome('Z');
			m_gangB->SetLastOutcome('Z');
			m_gangA->AddToScore(m_sentence.m_punishment);
			m_gangB->AddToScore(m_sentence.m_punishment);
		}
	}
	else {
		if (m_gangA->GetNumBetray() > m_gangB->GetNumBetray()) {
			m_gangA->SetLastOutcome('A');
			m_gangB->SetLastOutcome('B');
			m_gangA->AddToScore(m_sentence.m_leastBetrayed);
			m_gangB->AddToScore(m_sentence.m_mostBetrayed);
		}
		else if (m_gangA->GetNumBetray() > m_gangB->GetNumBetray()) {
			m_gangA->SetLastOutcome('B');
			m_gangB->SetLastOutcome('A');
			m_gangA->AddToScore(m_sentence.m_mostBetrayed);
			m_gangB->AddToScore(m_sentence.m_leastBetrayed);
		}
		else {
			m_gangA->SetLastOutcome('C');
			m_gangB->SetLastOutcome('C');
			m_gangA->AddToScore(m_sentence.m_sameBetrayed);
			m_gangB->AddToScore(m_sentence.m_sameBetrayed);
		}
	}


}
#include <iostream>
void GangGame::Run() {
	for (m_currentIteration = 0; m_currentIteration < m_totalIterations; ++m_currentIteration) {
		if (m_spiesActive) {
			m_gangA->PlantSpy(m_spyProb);
			m_gangB->PlantSpy(m_spyProb);
		}
		m_gangA->GetVotes();
		m_gangB->GetVotes();
		CheckForSpies();

		if (!ResolveSpies()) { // If no special spy business carry on as normal
			Resolve(m_gangA->GetDecision(), m_gangB->GetDecision());
		}
		std::cout << m_gangA->GetScore() << " " << m_gangB->GetScore() << std::endl;
	}
}

//TODO: Seperate these in normal game class as well
int GangGame::GetWinner() {
	if (m_gangA->GetScore() == m_gangB->GetScore()) {
		return m_draw;
	}
	else {
		return m_gangA->GetScore() < m_gangB->GetScore() ? m_gangA->GetID() : m_gangB->GetID();
	}
}

void GangGame::CheckForSpies() {
	if (!m_spiesActive) {
		return;
	}
	m_gangA->FindSpy();
	m_gangB->FindSpy();
}


// TODO: Refactor
bool GangGame::ResolveSpies() {
	if (!m_spiesActive) {
		return false;
	}

	if (m_gangA->DidFindSpy() && m_gangB->DidFindSpy()) {
		m_gangA->SetLastOutcome('?');
		m_gangB->SetLastOutcome('?');
		m_gangA->AddToScore(m_sentence.m_bothDiscoverSpy);
		m_gangB->AddToScore(m_sentence.m_bothDiscoverSpy);
	}
	else if (m_gangA->DidFindSpy()) {
		m_gangA->SetLastOutcome('?');
		m_gangB->SetLastOutcome('?');
		if (m_gangA->LeaderChanges()) {
			m_gangA->AddToScore(m_sentence.m_changeDiscoverSpy);
			m_gangB->AddToScore(m_sentence.m_spyUnmasked);
		}
		else {
			m_gangA->AddToScore(m_sentence.m_stickDiscoverSpy);
			m_gangB->AddToScore(m_sentence.m_spyUnmasked);
		}
	
	}
	else if (m_gangB->DidFindSpy()) {
		m_gangA->SetLastOutcome('?');
		m_gangB->SetLastOutcome('?');
		if (m_gangB->LeaderChanges()) {
			m_gangB->AddToScore(m_sentence.m_changeDiscoverSpy);
			m_gangA->AddToScore(m_sentence.m_spyUnmasked);
		}
		else {
			m_gangB->AddToScore(m_sentence.m_stickDiscoverSpy);
			m_gangA->AddToScore(m_sentence.m_spyUnmasked);
		}
	}
	else {
		return false;
	}
	return true;
}