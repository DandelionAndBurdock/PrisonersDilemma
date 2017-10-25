//#include "Game\GameManager.h"
//
//int main()
//{
//	GameManager game;
//	game.Run();
//
//}

#include "Game/GangGame.h"
#include "Game\Gang.h"

int main() {
	std::vector<std::string> vec = { "GangTournaments//Strat1.txt" , "GangTournaments//Strat1.txt" };
	Gang gang(1, vec);
	Gang gang2(2, vec);
	GangGame g(&gang, &gang2);
	g.Run();
}