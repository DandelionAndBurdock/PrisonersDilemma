#include "Game.h"
#include <iostream>

Game::Game(Prisoner& prisonerA, Prisoner& prisonerB, int iterationsPerGame, Sentence& sentence) :
Game(prisonerA, prisonerB, iterationsPerGame)
{
	m_maxSentence = m_sentence.m_punishment;
}

Game::Game(Prisoner& prisonerA, Prisoner& prisonerB, int iterationsPerGame) :
	m_prisonerA(prisonerA),
	m_prisonerB(prisonerB),
	m_totalIterations(iterationsPerGame),
	m_currentIteration(0),
	m_invalidStrategy(false)
{
	// Ensure prisoners start clean
	m_prisonerA.Reset();
	m_prisonerB.Reset();
}

Game::~Game()
{
}

bool Game::IsFinished() {
	if (m_invalidStrategy)
		return true;

	return (!Prisoner::HasValidStrategy(m_prisonerA.GetID()) || 
		!Prisoner::HasValidStrategy(m_prisonerB.GetID()));
}

int Game::GetWinner() const{
	if (!Prisoner::HasValidStrategy(m_prisonerA.GetID())) { // If a prisoner fails to make a selection (e.g. stuck in infinite loop) they auto lose
		return m_prisonerB.GetID();
	}
	if (!Prisoner::HasValidStrategy(m_prisonerB.GetID())) {
		return m_prisonerA.GetID();
	}
	if (m_prisonerA.GetScore() == m_prisonerB.GetScore()) {  
		return m_draw;
	}
	else {
		return m_prisonerA.GetScore() < m_prisonerB.GetScore() ? m_prisonerA.GetID() : m_prisonerB.GetID();
	}
}
void Game::Run() {

	for (m_currentIteration = 0; m_currentIteration < m_totalIterations; ++m_currentIteration) {
		if (IsFinished()) {
			break;
		}
		else {
			Resolve(m_prisonerA.GetSelection(), m_prisonerB.GetSelection());  
		}
	}


}

void Game::Resolve(const ActionType& choiceA, const ActionType& choiceB) { 
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
	else {
		ResolveInvalid(choiceA, choiceB);
	}
}

void Game::ResolveWW() {
	m_prisonerA.SetLastOutcome('W');
	m_prisonerB.SetLastOutcome('W');
	m_prisonerA.AddToScore(m_sentence.m_silent);
	m_prisonerB.AddToScore(m_sentence.m_silent);
}
void Game::ResolveXY() {
	m_prisonerA.SetLastOutcome('X');
	m_prisonerB.SetLastOutcome('Y');
	m_prisonerA.AddToScore(m_sentence.m_sucker);
	m_prisonerB.AddToScore(m_sentence.m_temptation);
}
void Game::ResolveYX() {
	m_prisonerA.SetLastOutcome('Y');
	m_prisonerB.SetLastOutcome('X');
	m_prisonerA.AddToScore(m_sentence.m_temptation);
	m_prisonerB.AddToScore(m_sentence.m_sucker);
}
void Game::ResolveZZ() {
	m_prisonerA.SetLastOutcome('Z');
	m_prisonerB.SetLastOutcome('Z');
	m_prisonerA.AddToScore(m_sentence.m_punishment);
	m_prisonerB.AddToScore(m_sentence.m_punishment);
}

void Game::ResolveInvalid(const ActionType& choiceA, const ActionType& choiceB) {
	if (choiceA == INVALID_ACTION) {
		m_prisonerA.SetValidStrategy(m_prisonerA.GetID(), false);
	}
	if (choiceB == INVALID_ACTION) {
		m_prisonerB.SetValidStrategy(m_prisonerB.GetID(), false);
	}
	std::cout << "Game error: Unrecognised outcomes" << std::endl;
	m_invalidStrategy = true;
}