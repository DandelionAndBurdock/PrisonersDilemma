#include "GangGame.h"

#include <iostream>

#include "Gang.h"

GangGame::GangGame(Gang* gangA, Gang* gangB, float spyProb, bool spiesActive, int numberIterations) :
	m_gangA(gangA), m_gangB(gangB), m_spyProb(spyProb), m_spiesActive(spiesActive), m_totalIterations(numberIterations)
{
	// Ensure gangs start clean
	m_gangA->Reset();
	m_gangB->Reset();
}	 


GangGame::~GangGame()
{
}

void GangGame::Resolve(ActionType choiceA, ActionType choiceB) {

	if (!m_gangA->IsMixed() && !m_gangB->IsMixed()) {

		if (choiceA == SILENCE && choiceB == SILENCE) {
			ResolveWW();
		}
		else if (choiceA == SILENCE && choiceB == BETRAY) {
			ResolveXY();
		}
		else if (choiceA == BETRAY && choiceB == SILENCE) {
			ResolveYX();
		}
		else if (choiceA == BETRAY && choiceB == BETRAY) {
			ResolveZZ();
		}
	}
	else {
		if (m_gangA->GetNumBetray() > m_gangB->GetNumBetray()) {
			ResolveAB();
		}
		else if (m_gangA->GetNumBetray() > m_gangB->GetNumBetray()) {
			ResolveBA();
		}
		else {
			ResolveCC();
		}
	}
}

void GangGame::ResolveWW() {
	m_gangA->SetLastOutcome('W');
	m_gangB->SetLastOutcome('W');
	m_gangA->AddToScore(m_sentence.m_silent);
	m_gangB->AddToScore(m_sentence.m_silent);
}

void GangGame::ResolveXY() {
	m_gangA->SetLastOutcome('X');
	m_gangB->SetLastOutcome('Y');
	m_gangA->AddToScore(m_sentence.m_sucker);
	m_gangB->AddToScore(m_sentence.m_temptation);
}

void GangGame::ResolveYX() {
	m_gangA->SetLastOutcome('Y');
	m_gangB->SetLastOutcome('X');
	m_gangA->AddToScore(m_sentence.m_temptation);
	m_gangB->AddToScore(m_sentence.m_sucker);
}

void GangGame::ResolveZZ() {
	m_gangA->SetLastOutcome('Z');
	m_gangB->SetLastOutcome('Z');
	m_gangA->AddToScore(m_sentence.m_punishment);
	m_gangB->AddToScore(m_sentence.m_punishment);
}

void GangGame::ResolveAB() {
	m_gangA->SetLastOutcome('A');
	m_gangB->SetLastOutcome('B');
	m_gangA->AddToScore(m_sentence.m_leastBetrayed);
	m_gangB->AddToScore(m_sentence.m_mostBetrayed);
}

void GangGame::ResolveBA() {
	m_gangA->SetLastOutcome('B');
	m_gangB->SetLastOutcome('A');
	m_gangA->AddToScore(m_sentence.m_mostBetrayed);
	m_gangB->AddToScore(m_sentence.m_leastBetrayed);
}

void GangGame::ResolveCC() {
	m_gangA->SetLastOutcome('C');
	m_gangB->SetLastOutcome('C');
	m_gangA->AddToScore(m_sentence.m_sameBetrayed);
	m_gangB->AddToScore(m_sentence.m_sameBetrayed);
}

void GangGame::Run() {
	for (m_currentIteration = 0; m_currentIteration < m_totalIterations; ++m_currentIteration) {
		if (IsFinished()) {
			return;
		}
		if (m_spiesActive) {
			 m_gangA->PlantSpy(m_spyProb / 2.0f);
			 m_gangB->PlantSpy(m_spyProb / 2.0f);
		}
		m_gangA->GetVotes();
		m_gangB->GetVotes();
		CheckForSpies();

		if (!ResolveSpies()) { // If no special spy business carry on as normal
			Resolve(m_gangA->GetDecision(), m_gangB->GetDecision());
		}
	}
}

bool GangGame::IsFinished() {
	return (!m_gangA->HasValidStrategy() ||
		!m_gangB->HasValidStrategy());
}

int GangGame::GetWinner() {
	if (!m_gangA->HasValidStrategy()) { // If a prisoner fails to make a selection (e.g. stuck in infinite loop) they auto lose
		return m_gangB->GetID();
	}
	if (!m_gangB->HasValidStrategy()) { 
		return m_gangA->GetID();
	}

	if (m_gangA->GetScore() == m_gangB->GetScore()) {
		return m_draw;
	}
	else {
		return m_gangA->GetScore() < m_gangB->GetScore() ? m_gangA->GetID() : m_gangB->GetID();
	}
}


void GangGame::PrintStatistics() const {
	std::cout << "Rounds Played: " << m_totalIterations << std::endl;
	std::cout << "Spy Probability: " << m_spyProb << std::endl;
	std::cout << "Spies Found: " << m_spyFoundLeaderChange + m_spyFoundLeaderStick << std::endl;
	std::cout << "Spies Missed:" << m_spyPresentNotFound << std::endl;
	std::cout << "Spies Found After Leader Switch: " << m_spyFoundLeaderChange << std::endl;
	std::cout << "Spies Found After Leader Stick: " << m_spyFoundLeaderStick << std::endl;
}

void GangGame::CheckForSpies() {
	if (!m_spiesActive) {
		return;
	}
	m_gangA->FindSpy();
	m_gangB->FindSpy();
}



bool GangGame::ResolveSpies() {
	if (!m_spiesActive) {
		return false;
	}
	if (m_gangA->DidFindSpy() && m_gangB->DidFindSpy()) {
		BothFindSpy();
		return true;
	}
	else if (m_gangA->DidFindSpy()) {
		GangAFindSpy();
		return true;
	}
	else if (m_gangB->DidFindSpy()) {
		GangBFindSpy();
		return true;
	}
	else {
		NoSpyFound();
		return false;
	}
	return true;
}

void GangGame::BothFindSpy() {
	m_gangA->SetLastOutcome('?');
	m_gangB->SetLastOutcome('?');
	m_gangA->AddToScore(m_sentence.m_bothDiscoverSpy);
	m_gangB->AddToScore(m_sentence.m_bothDiscoverSpy);
	if (m_gangA->LeaderChanges()) {
		++m_spyFoundLeaderChange;
	}
	else {
		++m_spyFoundLeaderStick;
	}
	if (m_gangB->LeaderChanges()) {
		++m_spyFoundLeaderChange;
	}
	else {
		++m_spyFoundLeaderStick;
	}
}
void GangGame::GangAFindSpy() {
	m_gangA->SetLastOutcome('?');
	m_gangB->SetLastOutcome('?');
	if (m_gangA->LeaderChanges()) {
		m_gangA->AddToScore(m_sentence.m_changeDiscoverSpy);
		m_gangB->AddToScore(m_sentence.m_spyUnmasked);
		++m_spyFoundLeaderChange;
	}
	else {
		m_gangA->AddToScore(m_sentence.m_stickDiscoverSpy);
		m_gangB->AddToScore(m_sentence.m_spyUnmasked);
		++m_spyFoundLeaderStick;
	}
	if (m_gangB->HasSpy()) {
		++m_spyPresentNotFound;
	}

}
void GangGame::GangBFindSpy() {
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
	if (m_gangA->HasSpy()) {
		++m_spyPresentNotFound;
	}
}

void GangGame::NoSpyFound() {
	if (m_gangA->HasSpy()) {
		++m_spyPresentNotFound;
	}
	if (m_gangB->HasSpy()) {
		++m_spyPresentNotFound;
	}
}