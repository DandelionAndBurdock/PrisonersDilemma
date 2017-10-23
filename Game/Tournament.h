// Class: Tournament
// Description: 
// Author: Philip Jones
// Date: 19/10/2017
#pragma once

#include "Prisoner.h"
#include "Game.h"

#include <string>
#include <vector>

#include "../Strategy/StrategyGenerator.h" 
#include "../Strategy/StrategyTester.h"
#include "../Utility/Matrix.h"

class Tournament
{
	enum Result { WIN, LOSE, DRAW, UNFINISHED }; //TODO: Can you handle draws?
public:
	Tournament(int ID, const std::string& fileDirectory = "", bool generateStrategies = true,
		int iterationsPerGame = 200, int numberOfPrisoners = 10,
		int punishmentSentence = 4, int temptationSentence = 0,
		int silentSentence = 2, int suckerSentence = 5);
	~Tournament();

	void RunTournament();
	void CalculateRankings();
private:
	void LoadPrisoners();
	void CreateNewStrategies();
	void LoadStrategies();
	void PlayGames();

	// Copy top n strategies to the directory Champions
	void MoveWinners(int n);

	//TODO: Need to implement copy/assingment operator (??)
	std::vector<Prisoner> m_prisoners; // List or prisoners in the tournament
	Matrix<Result> m_results; // Keep track of results for each prisoner
	std::vector<int> m_victories; //Keeps track of number of victories for each prisoner
	std::vector<int> m_draws; //Keeps track of number of draws for each prisoner
					  // Simulates a game for prisoner A and prisoner B and returns the ID of the winner
	void RunGame(Prisoner& prisonerA, Prisoner& prisonerB);


	int m_iterationsPerGame;
	int m_numberOfPrisoners;
	bool m_createNewStrategies;

	int m_ID;

	std::string m_directory;
	Game::Sentence m_payoffs;

	StrategyGenerator generator;
	StrategyTester tester;
};

//TODO: Rule of 3