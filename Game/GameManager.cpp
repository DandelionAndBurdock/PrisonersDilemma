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

int GameManager::GetUserInt() {
	int choice;

	std::string input;
	for (;;) {
		getline(std::cin, input);
		std::stringstream ss(input);
		if (input.find('.') == std::string::npos && ss >> choice) { // Check not a float and valid number
			return choice;
		}
		else {
			std::cout << "Please enter a valid integer" << std::endl;
		}
	}
}
float GameManager::GetUserFloat() {
	float choice;

	std::string input;
	for (;;) {
		getline(std::cin, input);
		std::stringstream ss(input);
		if (ss >> choice) { // Check not a float and valid number
			return choice;
		}
		else {
			std::cout << "Please enter a valid number" << std::endl;
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
	std::cout << "Welcome to Prisoners Dilemma! Snitches get itches..." << std::endl;
	// TODO: Enable disable strategy testing
}

void GameManager::ResolveInput(int input) {
	Selection selection = Selection(input);
	switch (selection) {
		case TOURNAMENT: {
			RunTournament();
			break;
		}
		case CHAMPIONSHIP: {
			RunChampionship();
			break;
		}
		case GENERATION:
			SetGenerationOptions();
			WriteConstantsToFile();
			break;
		case TOURNAMENT_OPTIONS: {
			SetTournamentOptions();
			break;
		}
	}

	std::cout << "Press enter to continue...";
	char c;
	c = getchar();

}

void GameManager::RunTournament() {
	Tournament t(0, m_numberOfPrisoners, m_generateStrategies, m_inputFileDirectory, m_outputFileDirectory,
		std::vector<std::string>(), m_numberOfWinners, m_iterationsPerGame, m_sentences);

	t.RunTournament();

	std::cout << "Would you like to see a breakdown of the games?" << std::endl;

	if (GetYesOrNo() == 'y') {
		t.PrintGameResults();
	}
}

void GameManager::RunChampionship() {
	Competition c(m_numberOfTournaments, m_numberOfPrisoners,
		m_numberOfWinners, m_generateStrategies,
		m_iterationsPerGame, m_inputFileDirectory,
		m_outputFileDirectory, m_sentences);

	c.RunCompetition();

	std::cout << "Would you like to see a breakdown of the games?" << std::endl;

	if (GetYesOrNo() == 'y') {
		c.PrintGameResults();
	}
}

void GameManager::SetGenerationOptions() {
	std::cout << "Configure options for strategy generation:" << std::endl << std::endl;
	SetIf();
	SetArithExpression();
	SetAddNewLine();
	SetGoto();
	SetCharExpression();
	SetMinLines();
	SetMaxLines();
	SetGotoJump();
}

void GameManager::SetTournamentOptions() {
	std::cout << "Configure options for strategy generation:" << std::endl << std::endl;
	ConfigureGangs();
	if (!m_gangs) {
		ConfigurePrisoners();
	}
	SetIterations();

}
// Sentences 
// Number of winners
// Generate new strategies

void GameManager::ConfigureGangs() {
	std::cout << "Would you like to use gangs?" << std::endl;
	if (GetYesOrNo() == 'y') {
		m_gangs = true;
		std::cout << std::endl;
	}
	else {
		m_gangs = false;
		std::cout << std::endl;
		return;
	}
	;
	ConfigureSpies();
}

void GameManager::ConfigurePrisoners() {
	std::cout << "Number of prisoners is currently " << m_numberOfPrisoners << std::endl;
	std::cout << "Would you like to change value?" << std::endl;
	if (GetYesOrNo() == 'y') {
		std::cout << "Enter new value:";
		m_numberOfPrisoners = GetUserInt();
		std::cout << std::endl;
	}
}

void GameManager::ConfigureSpies() {
	std::cout << "Would you like to use spies?" << std::endl;
	if (GetYesOrNo() == 'y') {
		m_spies = true;
		std::cout << std::endl;
	}
	else {
		m_spies = false;
		std::cout << std::endl;
		return;
	}

	std::cout << "Spy probability is currently" << m_spyProb << std::endl;
	std::cout << "Would you like to change value?" << std::endl;
	if (GetYesOrNo() == 'y') {
		std::cout << "Enter new value (between 0 and 1):";
		m_spyProb = GetUserFloat(); 
		std::cout << std::endl;
	}

	

}

void GameManager::SetIterations() {
	std::cout << "Number of iterations per game is currently " << m_iterationsPerGame << std::endl;
	std::cout << "Would you like to change value?" << std::endl;
	if (GetYesOrNo() == 'y') {
		std::cout << "Enter new value :";
		m_iterationsPerGame = GetUserInt();
		std::cout << std::endl;
	}
	else {
		std::cout << std::endl;
	}
}

void GameManager::SetIf() {
	std::cout << "Probability to generate an IF statement is currently " << m_ifProb << std::endl;
	std::cout << "Would you like to change value?" << std::endl;
	if (GetYesOrNo() == 'y') {
		std::cout << "Enter new value (between 0 and 1):";
		m_ifProb = GetUserFloat(); 
		std::cout << std::endl;
	}
	else {
		std::cout << std::endl;
	}
}

void GameManager::SetArithExpression() {
	std::cout << "Probability to extend an arithmetic expression is currently " << m_extendArithmeticProb << std::endl;
	std::cout << "Would you like to change value?" << std::endl;
	if (GetYesOrNo() == 'y') {
		std::cout << "Enter new value (between 0 and 1):";
		m_extendArithmeticProb = GetUserFloat(); 
		std::cout << std::endl;
	}
	else {
		std::cout << std::endl;
	}
}

void GameManager::SetAddNewLine() {
	std::cout << "Probability to add a new line is currently " << m_addLineProb << std::endl;
	std::cout << "Would you like to change value?" << std::endl;
	if (GetYesOrNo() == 'y') {
		std::cout << "Enter new value (between 0 and 1):";
		m_addLineProb = GetUserFloat();
		std::cout << std::endl;
	}
	else {
		std::cout << std::endl;
	}
}

void GameManager::SetGoto() {
	std::cout << "Probability to add a goto statement is currently " << m_gotoProb << std::endl;
	std::cout << "Would you like to change value?" << std::endl;
	if (GetYesOrNo() == 'y') {
		std::cout << "Enter new value (between 0 and 1):";
		m_gotoProb = GetUserFloat(); 
		std::cout << std::endl;
	}
	else {
		std::cout << std::endl;
	}
}

void GameManager::SetCharExpression() {
	std::cout << "Probability to add a character expression is currently " << m_charExpressionProb << std::endl;
	std::cout << "Would you like to change value?" << std::endl;
	if (GetYesOrNo() == 'y') {
		std::cout << "Enter new value (between 0 and 1):";
		m_charExpressionProb = GetUserFloat(); 
		std::cout << std::endl;
	}
	else {
		std::cout << std::endl;
	}
}

void GameManager::SetMinLines() {
	std::cout << "Minimum number of lines is currently " << m_minimumLineNumber << std::endl;
	std::cout << "Would you like to change value?" << std::endl;
	if (GetYesOrNo() == 'y') {
		std::cout << "Enter new value :";
		m_minimumLineNumber = GetUserInt(); 
		std::cout << std::endl;
	}
	else {
		std::cout << std::endl;
	}
}

void GameManager::SetMaxLines() {
	std::cout << "Maximum number of lines is currently " << m_maximumLineNumber << std::endl;
	std::cout << "Would you like to change value (enter 0 for no limit)?" << std::endl;
	if (GetYesOrNo() == 'y') {
		std::cout << "Enter new value :";
		m_maximumLineNumber = GetUserInt(); 
		std::cout << std::endl;
	}
	else {
		std::cout << std::endl;
	}
}

void GameManager::SetGotoJump() {
	std::cout << "Number of lines a goto statement will jump ahead is currently " << m_gotoForecast << std::endl;
	std::cout << "Would you like to change value?" << std::endl;
	if (GetYesOrNo() == 'y') {
		std::cout << "Enter new value :";
		m_gotoForecast = GetUserInt(); 
		std::cout << std::endl;
	}
	else {
		std::cout << std::endl;
	}
}


void GameManager::WriteConstantsToFile() {
	StrategyConstants constants;
	constants.ifProb = m_ifProb;
	constants.addLineProb = m_addLineProb;
	constants.charExpressionProb = m_charExpressionProb;
	constants.extendArithmeticProb = m_extendArithmeticProb;
	constants.gotoProb = m_gotoProb;
	constants.gotoForecast = m_gotoForecast;
	constants.maximumLineNumber = m_maximumLineNumber;
	constants.minimumLineNumber = m_minimumLineNumber;

	WriteConstants(constants);
	
}
// Select an option (1-9)
// 1. Run tournament // Run again
// 2. Set Strategy Generation Options
// 3, Set Tournament Options-> Iterations, punishments
// 4. Set Breeding Option
// 5. Select Strategy Language // PSL+++
// 6. Lodge a complaint --> What is the nature of your complaint?
// 7. Run gang tournament
