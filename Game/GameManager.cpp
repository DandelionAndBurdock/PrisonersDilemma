#include "GameManager.h"

#include <iostream>
#include <sstream>


#include "Tournament.h"
#include "Competition.h"

#include "../Strategy/StrategyConstants.h"

GameManager::GameManager() :
	 m_numberOfPrisoners(defaultPrisoners),
	m_numberOfTournaments(defaultTournaments),
	m_generateStrategies(defaultGenStrategies),
	m_iterationsPerGame(defaultIterations),
	m_inputFileDirectory(defaultInputDir),
	m_outputFileDirectory(defaultOutputDir),
	m_numberOfWinners(defaultWinners),
	m_sentences(Sentence())
{
	StrategyConstants constants = ReadConstants();

	m_charExpressionProb = constants.charExpressionProb;
	m_extendArithmeticProb = constants.extendArithmeticProb;
	m_addLineProb = constants.addLineProb;
	m_gotoProb = constants.gotoProb;
	m_ifProb = constants.ifProb;

	m_minimumLineNumber = constants.minimumLineNumber;
	m_maximumLineNumber = constants.maximumLineNumber;
	m_gotoForecast = constants.gotoForecast;
}


GameManager::~GameManager()
{
}

void GameManager::Run() {
	PrintWelcomeMessage();
	int input = 0;
	do {
		DisplayOptions();
		input = GetUserInput();
		ResolveInput(input);
	} while (input != 6);//TODO: UseEnum


}
// Note: This code will fail if given an end of file or exponential input e.g. 1E-1
int GameManager::GetUserInput() {
	int choice;
	
	std::string input;
	for (;;) {
		std::cout << "Enter an option (" << minUserOption << "-" << maxUserOption << "): " ;
		getline(std::cin, input);
		std::stringstream ss(input);
		if (input.find('.') == std::string::npos && ss >> choice) { // Check not a float and valid number
			if (choice < minUserOption || choice > maxUserOption) {	// Check valid range
				std::cout << "Please enter an integer between " << minUserOption << " and " << maxUserOption << std::endl;
			}
			else {
				return choice;
			}
		}
		else {
			std::cout << "Please enter a valid integer" << std::endl;
		}
	}
}

char GameManager::GetYesOrNo() {
	char choice;

	std::string input;
	for (;;) {
		std::cout << "Enter an option ([y]es or [n]o):";
		getline(std::cin, input);
		std::stringstream ss(input);
		if (ss >> choice && (tolower(choice) != 'y' || tolower(choice) != 'n')) {
				return tolower(choice);
		}
		else {
			std::cout << "Please enter y for yes or n for no" << std::endl;
		}
	}
}
void GameManager::DisplayOptions() {
	std::cout << "Please select an option (Enter 1-5)" << std::endl;
	std::cout << "1. Run tournament" << std::endl; 
	std::cout << "2. Run tournament of tournaments" << std::endl;
	std::cout << "3. Configure strategy generation options" << std::endl;
	std::cout << "4. Configure tournament options" << std::endl;
	std::cout << "5. Configure breeding settings" << std::endl;
	std::cout << "6. Lodge a complaint" << std::endl;
	std::cout << "7. Quit" << std::endl;
}

//TODO: Refactor
void GameManager::PrintWelcomeMessage() {
	std::cout << "Welcome to Prisoners Dilemma!" << std::endl;
	// TODO: Enable disable strategy testing
}

void GameManager::ResolveInput(int input) {
	Selection selection = Selection(input);
	switch (selection) {
	case TOURNAMENT: {
		Tournament t(0, m_numberOfPrisoners, m_generateStrategies, m_inputFileDirectory, m_outputFileDirectory,
			std::vector<std::string>(), m_numberOfWinners, m_iterationsPerGame, m_sentences);
		t.RunTournament();
		std::cout << "Would you like to see a breakdown of the games?" << std::endl;
		if (GetYesOrNo() == 'y') {
			t.PrintGameResults();
		}

		break;
	}
	case CHAMPIONSHIP: {
			Competition c(m_numberOfTournaments, m_numberOfPrisoners,
				m_numberOfWinners, m_generateStrategies,
				m_iterationsPerGame, m_inputFileDirectory,
				m_outputFileDirectory, m_sentences);
			c.RunCompetition();
			std::cout << "Would you like to see a breakdown of the games?" << std::endl;
			if (GetYesOrNo() == 'y') {
				c.PrintGameResults();
			}
			break;
		}
	case GENERATION:
		break;
	}
	std::cout << "Press enter to continue...";
	char c;
	c = getchar();
}
// Select an option (1-9)
// 1. Run tournament // Run again
// 2. Set Strategy Generation Options
// 3, Set Tournament Options-> Iterations, punishments
// 4. Set Breeding Option
// 5. Select Strategy Language // PSL+++
// 6. Lodge a complaint --> What is the nature of your complaint?
