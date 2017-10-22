// Class: Tournament
// Description: 
// Author: Philip Jones
// Date: 19/10/2017
#pragma once

#include "Prisoner.h"
#include "Game.h"

#include <string>

#include "StrategyGenerator.h" //TODO: Put these in same folder
#include "../StrategyTester.h"
#include "../Utility/Matrix.h"

class Tournament
{
	enum Result { WIN, LOSE, DRAW, UNFINISHED }; //TODO: Can you handle draws?
public:
	Tournament(const std::string& fileDirectory = "", bool generateStrategies = true,
		int iterationsPerGame = 200, int numberOfPrisoners = 10,
		int punishmentSentence = 4, int temptationSentence = 0,
		int silentSentence = 2, int suckerSentence = 5);
	~Tournament();

	bool RunTournament();

private:
	void LoadPrisoners();
	void CreateNewStrategies();
	void LoadStrategies();

	//TODO: Need to implement copy/assingment operator (??)
	std::vector<Prisoner> m_prisoners; // List or prisoners in the tournament
	Matrix<Result> results; // Keep track of number of victories
					  //TODO: Matrix to keep track of who beat who
					  // Simulates a game for prisoner A and prisoner B and returns the ID of the winner
	int RunGame(Prisoner& prisonerA, Prisoner& prisonerB);


	int m_iterationsPerGame;
	int m_numberOfPrisoners;
	bool m_createNewStrategies;
	std::string m_directory;
	Game::Sentence m_payoffs;

	StrategyGenerator generator;
	StrategyTester tester;
};