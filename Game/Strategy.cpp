#include "Strategy.h"


Strategy::Strategy(const std::string& filename, std::map<TokenValue, int*>& intVariables, std::map<TokenValue, char*> charVariables) :
	m_interpreter(filename, intVariables, charVariables)
{
}


Strategy::~Strategy()
{
}

ActionType Strategy::GetAction() {
	return m_interpreter.GetSelection();
}