//#include "Game\GameManager.h"
//
//int main()
//{
//	GameManager game;
//	game.Run();
//
//}

#include "Game/GangTournament.h"
#include "Game\Gang.h"
#include "Game\GangGame.h"
#include "Game\Tournament.h"

#include <chrono>
#include <fstream>
//Make this a profile function
int main() {
	// repeat the problem for various numbers of iterations
	std::vector<int> iterations = { 100, 200, 500, 1000, 2000, 4000, 5000, 7500, 10000 };
	// holds the time of each run

	std::vector<double> time;
	for (int number : iterations)
	{
		// Do Profiling
		auto startTime = std::chrono::high_resolution_clock::now();
		Tournament t(1, 10, false, defaultInputDir, defaultOutputDir, std::vector<std::string>(), 3, number); // Run Trials
		t.RunTournament();
		auto endTime = std::chrono::high_resolution_clock::now();
		time.push_back(std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count());
		// End Profiling
	}



	std::ofstream outFile("ProfilingTournamentIterations.csv");
	//TODO: Check doornumber and time have the same size
	outFile << "N" << "," << "Time (microsecs)" << std::endl;
	for (int i = 0; i < iterations.size(); ++i)
		outFile << iterations[i] << "," << time[i] << std::endl;

	//std::vector<std::string> vec = { "GangTournaments//Strat1.txt" ,
	//	"GangTournaments//Strat1.txt",
	//	"GangTournaments//Strat2.txt" ,
	//	"GangTournaments//Strat2.txt",
	//	"GangTournaments//Strat1.txt" };

	//std::vector<std::string> vec2 = { "GangTournaments//Strat3.txt" ,
	//	"GangTournaments//Strat3.txt",
	//	"GangTournaments//Strat3.txt" ,
	//	"GangTournaments//Strat3.txt",
	//	"GangTournaments//Strat3.txt" };
	//Gang gang(0, vec);
	//Gang gang2(1, vec);
	//Gang gang3(2, vec);
	//Gang gang4(3, vec);
	//Gang gang5(4, vec);
	//std::vector<Gang> vecG{ gang, gang2, gang3, gang4, gang5 };
	//GangTournament gt(1, vecG, true, 0.4, 100, 2);
	//gt.RunTournament();
}