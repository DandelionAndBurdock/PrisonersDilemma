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
	m_maxSentence = m_sentence.m_punishment;
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
	for (m_currentIteration = 0; m_currentIteration < m_totalIterations; ++m_currentIteration) {
		if (IsFinished()) {
			break;
		}
		else {
			Resolve(m_prisonerA.GetSelection(), m_prisonerB.GetSelection());
		}
	}
	if (m_prisonerA.GetScore() == m_prisonerB.GetScore()) {
		return m_draw;
	}
	else {
		return m_prisonerA.GetScore() < m_prisonerB.GetScore() ? m_prisonerA.GetID() : m_prisonerB.GetID();
	}

}

void Game::Resolve(ActionType choiceA, ActionType choiceB) {  //TODO: Could do some calculation rather than brute force?
	if (choiceA == SILENCE && choiceB == SILENCE) {
		m_prisonerA.SetLastOutcome('W');
		m_prisonerB.SetLastOutcome('W');
		m_prisonerA.AddToScore(m_sentence.m_silent);
		m_prisonerB.AddToScore(m_sentence.m_silent);
	}
	else if (choiceA == SILENCE && choiceB == BETRAY) {
		m_prisonerA.SetLastOutcome('X');
		m_prisonerB.SetLastOutcome('Y');
		m_prisonerA.AddToScore(m_sentence.m_sucker);
		m_prisonerB.AddToScore(m_sentence.m_temptation);
	}
	else if (choiceA == BETRAY && choiceB == SILENCE) {
		m_prisonerA.SetLastOutcome('Y');
		m_prisonerB.SetLastOutcome('X');
		m_prisonerA.AddToScore(m_sentence.m_temptation);
		m_prisonerB.AddToScore(m_sentence.m_sucker);
	}
	else if (choiceA == BETRAY && choiceB == BETRAY) {
		m_prisonerA.SetLastOutcome('Z');
		m_prisonerB.SetLastOutcome('Z');
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