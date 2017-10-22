#include "Strategy.h"


Strategy::Strategy(const std::string& filename, const std::map<TokenValue, int*>& intVariables, const std::map<TokenValue, char*>& charVariables) :
	m_interpreter(filename, intVariables, charVariables)
{
}


Strategy::~Strategy()
{
}

ActionType Strategy::GetAction() {
	return m_interpreter.GetSelection();
}
bool Strategy::IsValid() {
	return m_interpreter.IsValid();
}