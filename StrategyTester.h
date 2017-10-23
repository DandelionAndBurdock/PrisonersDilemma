// Class: Strategy Tester
// Description: Puts strategies through several random tests to try and
// catch strategies which get stuck in loops or cannot return an outcome
// Author: Philip Jones
// Date: 17/10/2017
#include "Game\Prisoner.h"



#pragma once
class StrategyTester
{
	const std::string robotFile = "RobotTester.txt"; //TODO: What if doesn't exist? Is file manager doing job?
public:
	StrategyTester();
	~StrategyTester();
	bool PassesTest(Prisoner& testSubject);

private:
	Prisoner m_robot; // Will just give random selections

};