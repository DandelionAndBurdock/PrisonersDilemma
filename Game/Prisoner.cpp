#include "Prisoner.h"
#include <iostream>

char Prisoner::outcomes[] = { 'W', 'X', 'Y', 'Z' };

Prisoner::Prisoner(int ID, const std::string& filename) :
	m_lastOutcome('?'), 
	m_alloutcomesW(0),
	m_alloutcomesX(0),
	m_alloutcomesY(0),
	m_alloutcomesZ(0),
	m_iterations(0),
	m_intVars(MakeIntegerVariableMap()),
	m_charVars(MakeCharVariableMap()),
	m_score(0),
	m_ID(ID),
	m_strategy(filename, m_intVars, m_charVars)
{}

Prisoner::~Prisoner()
{
}

// TODO: Check
Prisoner::Prisoner(const Prisoner& prisoner):
	m_intVars(MakeIntegerVariableMap()),
	m_charVars(MakeCharVariableMap())
{
	m_lastOutcome = prisoner.m_lastOutcome; 
	m_alloutcomesW= prisoner.m_alloutcomesW;
	m_alloutcomesX= prisoner.m_alloutcomesX;
	m_alloutcomesY= prisoner.m_alloutcomesY;
	m_alloutcomesZ= prisoner.m_alloutcomesZ;
	m_iterations = prisoner.m_iterations;
	m_score = prisoner.m_score;
	m_ID = prisoner.m_ID;
	m_strategy = prisoner.m_strategy;
}

Prisoner Prisoner::operator=(const Prisoner& prisoner) 
{
	if (this == &prisoner) {
		return *this;
	}
	m_lastOutcome = prisoner.m_lastOutcome; 
	m_alloutcomesW = prisoner.m_alloutcomesW;
	m_alloutcomesX = prisoner.m_alloutcomesX;
	m_alloutcomesY = prisoner.m_alloutcomesY;
	m_alloutcomesZ = prisoner.m_alloutcomesZ;
	m_iterations = prisoner.m_iterations;
	m_score = prisoner.m_score;
	m_ID = prisoner.m_ID;
	m_intVars = prisoner.m_intVars;
	m_charVars = prisoner.m_charVars;
	m_strategy = prisoner.m_strategy;
}

std::map<TokenValue, int*> Prisoner::MakeIntegerVariableMap() {//TODO: Make const pointers??
	return std::map<TokenValue, int*> {  	//TODO: Would be bettter if the outcomes were in an array/vector
										{ TokenValue::ALLOUTCOMES_W, &m_alloutcomesW }, 
										{ TokenValue::ALLOUTCOMES_X, &m_alloutcomesX },
										{ TokenValue::ALLOUTCOMES_Y, &m_alloutcomesY },
										{ TokenValue::ALLOUTCOMES_Z, &m_alloutcomesZ },
										{ TokenValue::ITERATIONS,    &m_iterations },
										{ TokenValue::MYSCORE,       &m_score },
									 };
}
std::map<TokenValue, char*> Prisoner::MakeCharVariableMap() { //TODO: Could use a loop and rely on ASCII
	return std::map<TokenValue, char*> { { TokenValue::LASTOUTCOME, &m_lastOutcome},
										 { TokenValue::W, outcomes + 0 },
										 { TokenValue::X, outcomes + 1 },
										 { TokenValue::Y, outcomes + 2 },
										 { TokenValue::Z, outcomes + 3 }};
}

void Prisoner::PrintDebugInfo() {
	std::cout << "LastOutcome:" << m_lastOutcome << std::endl;
	std::cout << "Alloutcomes W:" << m_alloutcomesW << std::endl;
	std::cout << "Alloutcomes X:" << m_alloutcomesX << std::endl;
	std::cout << "Alloutcomes Y:" << m_alloutcomesY << std::endl;
	std::cout << "Alloutcomes Z:" << m_alloutcomesZ << std::endl;
	std::cout << "Iterations:" << m_iterations << std::endl;	
	std::cout << "Score:" << m_score << std::endl;
}

void Prisoner::ChangeStrategy(const std::string& strategyFile) {
	m_strategy = Strategy(strategyFile, m_intVars, m_charVars);
}

ActionType Prisoner::GetSelection() {
	++m_iterations;
	return m_strategy.GetSelection();
}

void Prisoner::SetLastOutcome(char outcome){	
	m_lastOutcome = outcome; 
	//TODO: Would be bettter if the outcomes were in an array/vector
	switch (outcome) {
	case 'W':
		++m_alloutcomesW;
		break;
	case 'X':
		++m_alloutcomesX;
		break;
	case 'Y':
		++m_alloutcomesY;
		break;
	case 'Z':
		++m_alloutcomesZ;
		break;
	}
}

bool Prisoner::HasValidStrategy() {
	return m_strategy.IsValid();
}


void Prisoner::Reset() {
	m_alloutcomesW = 0;
	m_alloutcomesX = 0;
	m_alloutcomesY = 0;
	m_alloutcomesZ = 0;
	m_iterations = 0;
	m_score = 0;
}

std::string Prisoner::GetCode() {
	return m_strategy.GetCode();
}

void Prisoner::SetValidStrategy(bool isValid) {
	m_strategy.SetValidStrategy(false);
}
//TODO: Order of functions matches order of header files
