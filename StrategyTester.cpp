#include "StrategyTester.h"

#include "Game\Game.h"

StrategyTester::StrategyTester(Prisoner& testSubject) :
	m_prisoner(testSubject), m_robot(Prisoner(robotFile))
{

}


StrategyTester::~StrategyTester()
{
}

bool StrategyTester::PassesTest() { //TODO: This should accept a prisoner function parameter
	if (!m_prisoner.HasValidStrategy())
		return false;

	Game gameA(m_prisoner, m_robot, 10);
	gameA.GetWinner();
	if (!m_prisoner.HasValidStrategy())
		return false;

	Game gameB(m_robot, m_prisoner, 200);
	gameB.GetWinner();
	return m_prisoner.HasValidStrategy();
}