#include "Prisoner.h"


Prisoner::Prisoner(const std::string& filename) :
	m_strategy(filename, MakeIntegerVariableMap(), MakeCharVariableMap()),
	m_lastOutcome('?'), // TODO: Check
m_alloutcomesW(0),
m_alloutcomesX(0),
m_alloutcomesY(0),
m_alloutcomesZ(0),
m_iterations(0),
m_score(0)
{}

ActionType Prisoner::MakeSelection() {
	++m_iterations;
	return m_strategy.GetAction();
}

Prisoner::~Prisoner()
{
}

std::map<TokenValue, int*> Prisoner::MakeIntegerVariableMap() {
	return std::map<TokenValue, int*> { 
										{ TokenValue::ALLOUTCOMES_W, &m_alloutcomesW }, //TODO: Is there any way to automate this
										{ TokenValue::ALLOUTCOMES_X, &m_alloutcomesX },
										{ TokenValue::ALLOUTCOMES_Y, &m_alloutcomesY },
										{ TokenValue::ALLOUTCOMES_Z, &m_alloutcomesZ },
										{ TokenValue::ITERATIONS,    &m_iterations },
										{ TokenValue::MYSCORE,       &m_score },
									 };
}
std::map<TokenValue, char*> Prisoner::MakeCharVariableMap() {
	return std::map<TokenValue, char*> { {TokenValue::LASTOUTCOME, &m_lastOutcome} };//TODO: LASTOUTCOME->LAST_OUTCOME
}