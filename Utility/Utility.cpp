#include "Utility.h"


#include <string>

// Note: Not portable
#include "Windows.h" // For CreateDirectoryA() 

#include "../Game/PrisonersDilemmaGame.h"
#include "../Strategy/StrategyConstants.h"

#include "FileManager.h"

void Setup() {
	SetupDirectories();
	CreateRobot();
	CreateStrategyGenFile();
}

// TODO: Refactor -> Change c_strings to STL string variables
void SetupDirectories() {
	CreateDirectoryA(".//Tournaments", NULL);
	CreateDirectoryA(".//GangTournaments", NULL);
	CreateDirectoryA(".//Tournaments//Winners", NULL);
	CreateDirectoryA(".//GangTournaments//Winners", NULL);
	CreateDirectoryA(".//Tournaments//Winners//Champions", NULL);
	CreateDirectoryA(".//GangTournaments//Winners//Champions", NULL);
}

void CreateRobot() {
	FileManager::Instance()->WriteFile(".//RobotTester.txt", std::string("10 RANDOM"));
}

// TODO: Refactor -> Remove magic numbers define defaults in Strategy header
void CreateStrategyGenFile() {
	StrategyConstants parameters;
	parameters.addLineProb = 0.8;
	parameters.charExpressionProb = 0.3;
	parameters.extendArithmeticProb = 0.1;
	parameters.ifProb = 0.7;
	parameters.gotoProb = 0.7;
	parameters.gotoForecast = 3;
	parameters.maximumLineNumber = 10;
	parameters.minimumLineNumber = 3;
	WriteConstants(parameters);

}