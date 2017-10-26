//#include "Game\GameManager.h"
//
//int main()
//{
//	GameManager game;
//	game.Run();
//
//}
# include "Profiling\Profiling.h"

//Make this a profile function
#include <iostream>
#include "Game\GangTournament.h"
int main() {
	std::vector<std::string> vec = { "GangTournaments//Strat1.txt" ,
		"GangTournaments//Strat1.txt",
		"GangTournaments//Strat2.txt" ,
		"GangTournaments//Strat2.txt",
		"GangTournaments//Strat1.txt" };

	std::vector<std::string> vec2 = { "GangTournaments//Strat3.txt" ,
		"GangTournaments//Strat3.txt",
		"GangTournaments//Strat3.txt" ,
		"GangTournaments//Strat3.txt",
		"GangTournaments//Strat3.txt" };
	Gang gang(0, 5);
	Gang gang2(1, vec);
	Gang gang3(2, vec);
	Gang gang4(3, vec, false);
	Gang gang5(4, vec);
	std::vector<Gang> vecG{ gang, gang2, gang3, gang4, gang5 };
	GangTournament gt(1, vecG, true, 0.4, 100, 2);
	gt.RunTournament();
	gt.PrintSpyStatistics();

}