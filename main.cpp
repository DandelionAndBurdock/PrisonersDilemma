#include "Game/Game.h"
#include "Game\Prisoner.h"
#include <iostream>

int main()
{
	using namespace std;

	const std::string file = "H:\\Visual Studio 2013\\Projects\\PrisonersDilemma\\PrisonersDilemma\\Test.txt";
	//Interpreter test(file);
	//TODO: Make this unit test 1
	Prisoner p1("C:\\PD - Git\\PrisonersDilemma\\Test.txt");
	Prisoner p2("C:\\PD - Git\\PrisonersDilemma\\Test2.txt");

	std::cout << "********************\n";
	p1.PrintDebugInfo();
	p2.PrintDebugInfo();
	std::cout << "********************\n";
	Game game(p1, p2, 10);

	if (game.GetWinner() == Game::GameResult::PRISONER_A) {
		std::cout << "Prisoner A wins!" << std::endl;
	}
	else {
		std::cout << "Prisoner B wins!" << std::endl;
	}

}