#include "StrategyTester.h"

#include <iostream>

#include "../Game/Game.h"

StrategyTester::StrategyTester() :
	m_robot(Prisoner(-1, robotFile)) //TODO: ROBOT enum
{

}


StrategyTester::~StrategyTester()
{
}

bool StrategyTester::PassesTest(Prisoner& testSubject) { //TODO: This should accept a prisoner function parameter //TODO: have a bool you can toggle on and off
	if (!Prisoner::HasValidStrategy(testSubject.GetID()))
		return false;

	int numberOfTests = 5; //TODO: Accept this as a parameter
	for (int i = 0; i < numberOfTests; ++i){
		Game gameA(testSubject, m_robot, 200); //TODO: Magic Numbers
		gameA.Run();
		if (!Prisoner::HasValidStrategy(testSubject.GetID())) {
			std::cout << "Failed test" << std::endl;
			return false;
		}

		Game gameB(m_robot, testSubject, 200); //TODO: Magic Numbers
		gameB.Run();
		if (!Prisoner::HasValidStrategy(testSubject.GetID())) {
			std::cout << "Failed test" << std::endl;
			return false;
		}
			
	}
	return true;
}



