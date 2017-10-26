#pragma once

#include "../Prisoner.h"

class GangPrisoner : public Prisoner {
protected:
	const char gangOutcomes[3] = { 'A', 'B', 'C' }; //TODO: Remove Magic Number

public:
	GangPrisoner(int ID, const std::string& strategy);//TODO: Strategy file path

protected:
	//TOOD: Should be capital o
	int m_alloutcomesA;	  // TODO: Comment
	int m_alloutcomesB;
	int m_alloutcomesC;

	void Reset() override;

	IntMap  MakeIntegerVariableMap() override;
	CharMap MakeCharVariableMap()    override;

};
