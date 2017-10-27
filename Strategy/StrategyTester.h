// Class: Strategy Tester
// Description: Puts strategies through several random tests to try and
// catch strategies which get stuck in loops or cannot return an outcome
// Author: Philip Jones
// Date: 17/10/2017
#include "../Game/Prisoner.h"



#pragma once
class StrategyTester
{
	// Simple strategy for testing strategies
	const std::string robotFile = "RobotTester.txt";
public:
	StrategyTester();
	~StrategyTester();

	// Returns true if the testSubject can play a game against a robot 
	// without getting stuck in infinite loops
	bool PassesTest(Prisoner& testSubject);

private:
	Prisoner m_robot; // Robot prisoner for testSubject to play games against

};