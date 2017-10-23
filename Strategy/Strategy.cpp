#include "Strategy.h"


Strategy::Strategy(const std::string& filename, const IntMap& intVariables, const CharMap& charVariables) :
	m_interpreter(filename, intVariables, charVariables)
{
}


Strategy::~Strategy()
{
}

Strategy& Strategy::operator=(const Strategy& rhs) {
	m_interpreter = rhs.m_interpreter;
	return *this;
}

ActionType Strategy::GetSelection() {
	return m_interpreter.GetSelection();
}
bool Strategy::IsValid() {
	return m_interpreter.IsValid();
}

std::string Strategy::GetCode() {
	return m_interpreter.GetCode();
}

void Strategy::SetValidStrategy(bool isValid) {
	m_interpreter.SetValidStrategy(isValid);
}