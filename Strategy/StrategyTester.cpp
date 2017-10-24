#include "StrategyTester.h"

#include "../Game/Game.h"

StrategyTester::StrategyTester() :
	m_robot(Prisoner(-1, robotFile)) //TODO: ROBOT enum
{

}


StrategyTester::~StrategyTester()
{
}

bool StrategyTester::PassesTest(Prisoner& testSubject) { //TODO: This should accept a prisoner function parameter //TODO: have a bool you can toggle on and off
	if (!testSubject.HasValidStrategy())
		return false;

	int numberOfTests = 10; //TODO: Accept this as a parameter
	for (int i = 0; i < numberOfTests; ++i){
		Game gameA(testSubject, m_robot, 200); //TODO: Magic Numbers
		gameA.GetWinner();
		if (!testSubject.HasValidStrategy())
			return false;

		Game gameB(m_robot, testSubject, 200); //TODO: Magic Numbers
		gameB.GetWinner();
		if (!testSubject.HasValidStrategy())
			return false;
	}
	return true;
}

