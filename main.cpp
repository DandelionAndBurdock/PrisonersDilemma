#include "Game/Game.h"
#include "Game\Prisoner.h"
#include "Game\StrategyGenerator.h"
#include <iostream>

int main()
{
	using namespace std;

	const std::string file = "H:\\Visual Studio 2013\\Projects\\PrisonersDilemma\\PrisonersDilemma\\Test.txt";
	//Interpreter test(file);
	//TODO: Make this unit test 1

	StrategyGenerator sg;
	//sg.GenerateStrategy("C:\\PD - Git\\PrisonersDilemma\\Test.txt");
	//sg.GenerateStrategy("C:\\PD - Git\\PrisonersDilemma\\Test2.txt");
	Prisoner p1("C:\\PD - Git\\PrisonersDilemma\\Test.txt");
	Prisoner p2("C:\\PD - Git\\PrisonersDilemma\\Test2.txt");
	if (!p1.HasValidStrategy()) {
		std::cout << "Invalid ";
		return -1;
	}


	Game game(p1, p2, 10);

	if (game.GetWinner() == Game::GameResult::PRISONER_A) {
		std::cout << "Prisoner A wins!" << std::endl;
	}
	else {
		std::cout << "Prisoner B wins!" << std::endl;
	}

}