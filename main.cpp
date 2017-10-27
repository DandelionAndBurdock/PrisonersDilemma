#include "Game\GameManager.h"

#include "Utility\Utility.h"

int main()
{
	Setup();
	GameManager game;
	game.Run();

}
//# include "Profiling\Profiling.h"
//
////Make this a profile function
//#include <iostream>
//#include "Game\Gangs\Gang.h"
//#include "Game\Gangs\GangTournament.h"
//#include <fstream>
//#include "Utility\FileManager.h"
//int main() {
//
//	std::vector<std::string> winners = { "GangTournaments//Win1.txt" ,
//		"GangTournaments//Win2.txt",
//		"GangTournaments//Win3.txt" ,
//		"GangTournaments//Win4.txt",
//		"GangTournaments//Win5.txt" };
//
//
//	std::vector<float> averagesStickStick;
//
//	std::vector<Gang> gangs;
//	Gang champs(0, winners, false);
//	gangs.push_back(champs);
//	for (int j = 0; j < 4; ++j) {
//		gangs.push_back(Gang(j + 1, 5, false));
//	}
//	GangTournament tournament(1, gangs, defaultGangInDir, defaultGangOutDir, true, 0.2);
//}
//		int numberOfReps = 10;
//			
//	for (float prob = 0.0f; prob <= 1.0001f; prob += 0.05f) {
//		int averageScore = 0;
//		for (int i = 0; i < numberOfReps; ++i) {
//			GangTournament tournament(1, gangs, defaultGangInDir, defaultGangOutDir, true, prob);
//			tournament.RunTournament();
//			averageScore += tournament.GetScore(champs.GetID());
//		}
//		averagesStickStick.push_back(averageScore / (float)numberOfReps);
//	}
//	
//	std::vector<float> averagesChangeStick;
//	for (auto& gang : gangs) {
//		gang.SetLeaderChange(true);
//	}
//	for (float prob = 0.0f; prob <= 0.20001f; prob += 0.01f) {
//		int averageScore = 0;
//		for (int i = 0; i < numberOfReps; ++i) {
//			GangTournament tournament(1, gangs, defaultGangInDir, defaultGangOutDir, true, prob);
//			tournament.RunTournament();
//			averageScore += tournament.GetScore(champs.GetID());
//		}
//		averagesChangeStick.push_back(averageScore / (float)numberOfReps);
//	}
//
//	std::vector<float> averagesChangeChange;
//	for (float prob = 0.0f; prob <= 1.0001f; prob += 0.05f) {
//		int averageScore = 0;
//		for (int i = 0; i < numberOfReps; ++i) {
//			GangTournament tournament(1, gangs, defaultGangInDir, defaultGangOutDir, true, prob);
//			tournament.RunTournament();
//			averageScore += tournament.GetScore(champs.GetID());
//		}
//		averagesChangeChange.push_back(averageScore / (float)numberOfReps);
//	}
//
//	std::ofstream outFile("SpyDependence.csv");
//	outFile << "Prob" << "," << "Leader Sticks Opponents Stick" << "," << "Leader Changes Opponent Sticks" 
//		<< "," << "Leader Changes Opponent Changes" << std::endl;
//	int i = 0;
//	for (float prob = 0.0f; prob <= 1.0001f; prob += 0.05f, ++i) {
//		outFile << prob << "," << averagesStickStick[i] << "," << averagesChangeStick[i] << ","
//			<< averagesChangeChange[i] << std::endl;
//	}
//	
//	
//}