// Class: Tournament
// Description: 
// Author: Philip Jones
// Date: 19/10/2017
#pragma once

#include "Prisoner.h"
#include "Game.h"

#include <string>
#include <set>
#include <vector>

#include "../Strategy/StrategyGenerator.h" 
#include "../Strategy/StrategyTester.h"
#include "../Utility/Matrix.h"

class Tournament
{
	enum Result { WIN, LOSE, DRAW, UNFINISHED }; 
public:
	Tournament(int ID, int numberOfPrisoners = defaultPrisoners, bool generateStrategies = defaultGenStrategies,
		const std::string& inputFileDirectory = defaultInputDir, const std::string& outputFileDirectory = defaultOutputDir,
		std::vector<std::string>& strategyFileNames = std::vector<std::string>(), int numberOfWinners = defaultWinners, int iterationsPerGame = defaultIterations,
		Sentence sentences = Sentence());

	
	~Tournament();

	// Plays games of tournament, saves winning strategies and generates output
	void RunTournament();

	// Displays which prisoner beat which other prisoner
	void PrintGameResults();

private:
	//TODO: Generates statistics and tournament information to the console and the file /
	void CalculateRankings();

	 // Loads m_numberOfPrisoners into m_prisoners vector
	void LoadPrisoners();

	// Creates prisoners with strategies generated by m_generator
	void CreateNewStrategies();

	// Creates prisoners with strategies loaded from m_inputDirector
	void LoadStrategies();

	// Runs all games in the tournament
	void PlayGames();

	// Simulates a game for prisoner A and prisoner B and returns the ID of the winner
	void RunGame(Prisoner& prisonerA, Prisoner& prisonerB);

	// Copies top m_numberOfWinners strategies to the output directory 
	void MoveWinners();

	// Generate statistics for the user about the tournament
	void PrintReport();

	//Helper functions for PrintReport()
	void PrintIntro();
	void PrintHeader();
	void PrintPrisonerPerformance();


	std::vector<Prisoner> m_prisoners;  // List or prisoners in the tournament
	Matrix<Result>        m_results;    // Keep track of outcome of game for each pair of prisoners
	Matrix<int>			  m_gameScores; // Keep track of scores in each game
	std::vector<int>      m_scores;	    // Keeps track of cumulative score
	std::vector<int>      m_victories;  // Keeps track of number of victories for each prisoner
	std::vector<int>      m_draws;      // Keeps track of number of draws for each prisoner
	


	int  m_iterationsPerGame;			// Number of iterations for each game in the tournament
	int  m_numberOfWinners;				// Number of winning strategies to save in the output directory
	int  m_numberOfPrisoners;			// Number of prisoners competing in the tournament
	bool m_createNewStrategies;			// Should generate new strategies

	int m_ID;							// Identifaction number for this tournament

	std::string m_inputDirectory;		// Folder to read strategies from (or generate new strategies too)
	std::string m_outputDirectory;		// Folder to write winning strategies and statistics
	Sentence    m_payoffs;			    // Contains the score changes for all possible game outcomes
	
	StrategyGenerator m_generator;		// Generates new strategies
	StrategyTester	  m_tester;			// Tests new strategies to catch infinite loops

	std::vector<std::string> m_strategyFileNames; // Contains file

	std::set<std::pair<int, int>, Comparison> m_rankings; // Will hold pair of victories/ ID 

};

//TODO: Rule of 3