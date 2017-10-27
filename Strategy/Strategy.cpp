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

