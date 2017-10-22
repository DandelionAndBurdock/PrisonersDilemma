#include "Game.h"
#include <iostream>

Game::Game(Prisoner& prisonerA, Prisoner& prisonerB, int iterationsPerGame, Sentence& sentence) :
m_prisonerA(prisonerA),
m_prisonerB(prisonerB),
m_iterations(iterationsPerGame),
m_sentence(sentence),
m_currentIteration(0)
{
	m_maxSentence = m_sentence.punishmentSentence; //TODO: Should make this variable
}

Game::Game(Prisoner& prisonerA, Prisoner& prisonerB, int iterationsPerGame) :
	m_prisonerA(prisonerA),
	m_prisonerB(prisonerB),
	m_iterations(iterationsPerGame),
	m_sentence(Sentence()),
	m_currentIteration(0)
{
	m_maxSentence = m_sentence.punishmentSentence; //TODO: Should make this variable
}



Game::~Game()
{
}

bool Game::IsFinished() {
	if (m_currentIteration > m_iterations / 2) { // Check if we can get an early exit
		return GetScoreDifference() > GetMaxScoreChange();
	}
	else {
		return false;
	}
}

Game::GameResult Game::GetWinner() {
	for (m_currentIteration = 0; m_currentIteration < m_iterations; ++m_currentIteration) {
		if (IsFinished()) { //TODO: Check this works in a draw
			break; //TODO: Check early exit workds
		}
		else {
			Resolve(m_prisonerA.MakeSelection(), m_prisonerB.MakeSelection());
		}
	}

	return m_prisonerA.GetScore() > m_prisonerB.GetScore() ? GameResult::PRISONER_A : GameResult::PRISONER_B;
}

void Game::Resolve(ActionType choiceA, ActionType choiceB) {
	if (choiceA == SILENCE && choiceB == SILENCE) { //TODO: Could do some calculation rather than brute force?
		m_prisonerA.SetLastOutcome('W');
		m_prisonerB.SetLastOutcome('W');
		m_prisonerB.AddToScore(m_sentence.silentSentence);
		m_prisonerB.AddToScore(m_sentence.silentSentence);
	}
	else if (choiceA == SILENCE && choiceB == BETRAY) { //TODO: This seems inefficient
		m_prisonerA.SetLastOutcome('X');
		m_prisonerB.SetLastOutcome('Y');
		m_prisonerA.AddToScore(m_sentence.suckerSentence);
		m_prisonerB.AddToScore(m_sentence.temptationSentence);
	}
	else if (choiceA == BETRAY && choiceB == SILENCE) { //TODO: This seems inefficient
		m_prisonerA.SetLastOutcome('Y');
		m_prisonerB.SetLastOutcome('X');
		m_prisonerA.AddToScore(m_sentence.temptationSentence);
		m_prisonerB.AddToScore(m_sentence.suckerSentence);
	}
	else if (choiceA == BETRAY && choiceB == BETRAY) { //TODO: This seems inefficient
		m_prisonerA.SetLastOutcome('Z');
		m_prisonerB.SetLastOutcome('Z');
		m_prisonerA.AddToScore(m_sentence.punishmentSentence);
		m_prisonerB.AddToScore(m_sentence.punishmentSentence);
	}
	else {
		std::cout << "Game error: Unrecognised outcomes" << std::endl;
	}
}