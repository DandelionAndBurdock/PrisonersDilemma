#include "GangPrisoner.h"

GangPrisoner::GangPrisoner(int ID, const std::string& strategy) :
	Prisoner(ID)
{
	m_intVars = MakeIntegerVariableMap();
	m_charVars = MakeCharVariableMap();
	m_strategy = Strategy(strategy, m_intVars, m_charVars);
	Prisoner::Reset();
	GangPrisoner::Reset();

}

IntMap  GangPrisoner::MakeIntegerVariableMap() {
	IntMap baseMap = Prisoner::MakeIntegerVariableMap();
	IntMap derivedMap = IntMap{
		{ TokenValue::ALLOUTCOMES_A, &m_alloutcomesA },
		{ TokenValue::ALLOUTCOMES_B, &m_alloutcomesB },
		{ TokenValue::ALLOUTCOMES_C, &m_alloutcomesX },
	};
	baseMap.insert(derivedMap.begin(), derivedMap.end());
	return baseMap;
};

CharMap GangPrisoner::MakeCharVariableMap() {
	CharMap baseMap = Prisoner::MakeCharVariableMap();
	CharMap derivedMap = CharMap{ { TokenValue::A, gangOutcomes + 0 },
	{ TokenValue::B, gangOutcomes + 1 },
	{ TokenValue::C, gangOutcomes + 2 } };
	baseMap.insert(derivedMap.begin(), derivedMap.end());
	return baseMap;
}

void GangPrisoner::Reset() {
	Prisoner::Reset();
	m_alloutcomesA = 0;
	m_alloutcomesB = 0;
	m_alloutcomesC = 0;
}