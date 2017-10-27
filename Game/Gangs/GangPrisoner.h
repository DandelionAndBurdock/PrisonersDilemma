#pragma once

#include "../Prisoner.h"

class GangPrisoner : public Prisoner {
protected:
	// Mixed response game outcomes specific to gangs
	const char gangOutcomes[3] = { 'A', 'B', 'C' }; // A - Most Betrays, B - Least Betrays, C - Equal Betrays

public:
	// Creates a prisoner by loading the strategy at strategyFilePath
	GangPrisoner(int ID, const std::string& strategyFilePath);

protected:
	// Sets game variables to default values
	void Reset() override;

	int m_alloutcomesA;	  // Number of times outcome A has occured
	int m_alloutcomesB;   // Number of times outcomes B has occured
	int m_alloutcomesC;   // Number of times outcomes C has occured

	// Creates map from integer keywords to pointers to the variable
	IntMap  MakeIntegerVariableMap() override;
	// Creates map from character keywords to pointers to the variable
	CharMap MakeCharVariableMap()    override;

};
