#include "StrategyTester.h"

#include "Game\Game.h"

StrategyTester::StrategyTester() :
	m_robot(Prisoner(-1, robotFile)) //TODO: ROBOT enum
{

}


StrategyTester::~StrategyTester()
{
}

bool StrategyTester::PassesTest(Prisoner& testSubject) { //TODO: This should accept a prisoner function parameter
	if (!testSubject.HasValidStrategy())
		return false;

	Game gameA(testSubject, m_robot, 10); //TODO: Magic Numbers
	gameA.GetWinner();
	if (!testSubject.HasValidStrategy())
		return false;

	Game gameB(m_robot, testSubject, 200);
	gameB.GetWinner();
	return testSubject.HasValidStrategy();
}

