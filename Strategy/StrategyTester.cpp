#include "StrategyTester.h"

#include <iostream>

#include "../Game/Game.h"

StrategyTester::StrategyTester() :
	m_robot(Prisoner(-1, robotFile)) 
{

}

StrategyTester::~StrategyTester()
{
}

//TODO: Refactor->Restructure and remove magic numbers
// accept numberOfTests as a parameter
bool StrategyTester::PassesTest(Prisoner& testSubject) { 
	if (!Prisoner::HasValidStrategy(testSubject.GetID()))
		return false;

	int numberOfTests = 5; 
	std::cout << "Testing Prisoner " << testSubject.GetID() << " for infinite loops" << std::endl;
	for (int i = 0; i < numberOfTests; ++i){
		Game gameA(testSubject, m_robot, 200); 
		gameA.Run();
		if (!Prisoner::HasValidStrategy(testSubject.GetID())) {
			std::cout << "Failed test" << std::endl;
			return false;
		}

		Game gameB(m_robot, testSubject, 200); 
		gameB.Run();
		if (!Prisoner::HasValidStrategy(testSubject.GetID())) {
			std::cout << "Failed test" << std::endl;
			return false;
		}
			
	}
	return true;
}



