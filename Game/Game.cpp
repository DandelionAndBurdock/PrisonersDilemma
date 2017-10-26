#include "Game.h"
#include <iostream>

Game::Game(Prisoner& prisonerA, Prisoner& prisonerB, int iterationsPerGame, Sentence& sentence) :
Game(prisonerA, prisonerB, iterationsPerGame) //TODO: This constructor overloading is not correct
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

	//TODO: Should check which type of sentence is highest
	m_maxSentence = m_sentence.m_punishment; //TODO: Is this still necessary
}

Game::~Game()
{
}

bool Game::IsFinished() {
	if (m_invalidStrategy)
		return true;
	else {
		return false;
	}

}

int Game::GetWinner() {
	if (!m_prisonerA.HasValidStrategy()) {
		return m_prisonerB.GetID();
	}
	if (!m_prisonerB.HasValidStrategy()) {
		return m_prisonerA.GetID();
	}
	if (m_prisonerA.GetScore() == m_prisonerB.GetScore()) {  //TODO: Lock
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
			Resolve(m_prisonerA.GetSelection(), m_prisonerB.GetSelection());  //TODO: Lock?
		}
	}


}

void Game::Resolve(ActionType choiceA, ActionType choiceB) {  //TODO: Could do some calculation rather than brute force?
	if (choiceA == SILENCE && choiceB == SILENCE) {
		m_prisonerA.SetLastOutcome('W'); //TODO: Lock
		m_prisonerB.SetLastOutcome('W'); //TODO: Lock
		m_prisonerA.AddToScore(m_sentence.m_silent);
		m_prisonerB.AddToScore(m_sentence.m_silent);
	}
	else if (choiceA == SILENCE && choiceB == BETRAY) {
		m_prisonerA.SetLastOutcome('X');  //TODO: Lock
		m_prisonerB.SetLastOutcome('Y');  //TODO: Lock
		m_prisonerA.AddToScore(m_sentence.m_sucker);
		m_prisonerB.AddToScore(m_sentence.m_temptation);
	}
	else if (choiceA == BETRAY && choiceB == SILENCE) {
		m_prisonerA.SetLastOutcome('Y');  //TODO: Lock
		m_prisonerB.SetLastOutcome('X');  //TODO: Lock
		m_prisonerA.AddToScore(m_sentence.m_temptation);
		m_prisonerB.AddToScore(m_sentence.m_sucker);
	}
	else if (choiceA == BETRAY && choiceB == BETRAY) {
		m_prisonerA.SetLastOutcome('Z');  //TODO: Lock
		m_prisonerB.SetLastOutcome('Z');  //TODO: Lock
		m_prisonerA.AddToScore(m_sentence.m_punishment);
		m_prisonerB.AddToScore(m_sentence.m_punishment);
	}
	else {
		if (choiceA == INVALID_ACTION) {
			m_prisonerA.SetValidStrategy(false);
		}
		if (choiceB == INVALID_ACTION) {
			m_prisonerB.SetValidStrategy(false);
		}
		std::cout << "Game error: Unrecognised outcomes" << std::endl;
		m_invalidStrategy = true;
	}
}