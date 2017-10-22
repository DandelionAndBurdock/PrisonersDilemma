#include "Game/Game.h"
#include "Game\Prisoner.h"
#include <iostream>

int main()
{
	using namespace std;

	const std::string file = "H:\\Visual Studio 2013\\Projects\\PrisonersDilemma\\PrisonersDilemma\\Test.txt";
	//Interpreter test(file);
	//TODO: Make this unit test 1
	Prisoner p1("C:\\PrisonersDilemma\\PrisonersDilemma\\Test.txt");
	Prisoner p2("C:\\PrisonersDilemma\\PrisonersDilemma\\Test2.txt");
	Game game(p1, p2, 10);

	if (game.GetWinner() == Game::GameResult::PRISONER_A) {
		std::cout << "Prisoner A wins!" << std::endl;
	}
	else {
		std::cout << "Prisoner B wins!" << std::endl;
	}

}