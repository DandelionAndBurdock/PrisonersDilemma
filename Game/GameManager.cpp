#include "GameManager.h"

#include <iostream>
#include <sstream>

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Run() {
	PrintWelcomeMessage();
	DisplayOptions();
	int input = GetUserInput();

}
// Note: This code will fail if given an input e.g. 1E-1
int GameManager::GetUserInput() {
	int choice;
	
	std::string input;
	for (;;) {
		std::cout << "Enter an option: ";
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
void GameManager::DisplayOptions() {
	std::cout << "Please select an option (Enter 1-5)" << std::endl;
	std::cout << "1. Run tournament" << std::endl; 
	std::cout << "2. Run tournament of tournaments" << std::endl;
	std::cout << "3. Configure strategy generation options" << std::endl;
	std::cout << "4. Configure tournament options" << std::endl;
	std::cout << "5. Configure breeding settings" << std::endl;
	std::cout << "6. Lodge a complaint" << std::endl;
}

//TODO: Refactor
void GameManager::PrintWelcomeMessage() {
	std::cout << "Welcome to Prisoners Dilemma!" << std::endl;
	// TODO: Enable disable strategy testing
}

// Select an option (1-9)
// 1. Run tournament // Run again
// 2. Set Strategy Generation Options
// 3, Set Tournament Options-> Iterations, punishments
// 4. Set Breeding Option
// 5. Select Strategy Language // PSL+++
// 6. Lodge a complaint --> What is the nature of your complaint?