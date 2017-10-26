#pragma once

#include <set>
#include <vector>

#include "../Utility/Matrix.h"

#include "PrisonersDilemmaGame.h"
#include <memory>

//TODO: Derive from tournament
#include "Gang.h"

class GangTournament
{
	enum Result { WIN, LOSE, DRAW, UNFINISHED };
public:
	GangTournament(int ID, std::vector<Gang>& gangs, const std::string& inputDirectory = defaultGangInDir, 
		const std::string& outputDirectory = defaultGangOutDir, bool useSpies = false,
		float spyProb = 0.0f, int numberIterations = 200, int numberOfWinners = 2);
	~GangTournament();

	// Plays games of tournament, saves winning strategies and generates output
	void RunTournament();

	// Displays which prisoner beat which other prisoner
	void PrintGameResults();

	void PrintSpyStatistics();
private:
	//TODO: Generates statistics and tournament information to the console and the file /
	void CalculateRankings();


	// Creates prisoners with strategies loaded from m_inputDirector
	void LoadStrategies();

	// Runs all games in the tournament
	void PlayGames();

	// Simulates a game for prisoner A and prisoner B and returns the ID of the winner
	void RunGame(Gang& gangA, Gang& gangB);

	// Copies top m_numberOfWinners strategies to the output directory 
	void MoveWinners();

	// Generate statistics for the user about the tournament
	void PrintReport();

	//Helper functions for PrintReport()
	void PrintIntro();
	void PrintHeader();
	void PrintPrisonerPerformance();


	std::vector<Gang>	  m_gangs;		// List or prisoners in the tournament
	Matrix<Result>        m_results;    // Keep track of outcome of game for each pair of prisoners
	Matrix<int>			  m_gameScores; // Keep track of scores in each game
	std::vector<int>      m_scores;	    // Keeps track of cumulative score
	std::vector<int>      m_victories;  // Keeps track of number of victories for each prisoner
	std::vector<int>      m_draws;      // Keeps track of number of draws for each prisoner



	int  m_iterationsPerGame;			// Number of iterations for each game in the tournament
	int  m_numberOfWinners;				// Number of winning strategies to save in the output directory
	//bool m_createNewStrategies;			// Should generate new strategies

	int m_ID;							// Identifaction number for this tournament

	std::string m_inputDirectory;		// Folder to read strategies from (or generate new strategies too)
	std::string m_outputDirectory;		// Folder to write winning strategies and statistics
	GangSentence    m_payoffs;			    // Contains the score changes for all possible game outcomes

	//StrategyGenerator m_generator;		// Generates new strategies
	//StrategyTester	  m_tester;			// Tests new strategies to catch infinite loops

	std::vector<std::string> m_strategyFileNames; //TODO: Is this used?

	std::set<std::pair<int, int>, Comparison> m_rankings; // Will hold pair of victories/ ID 


	bool m_useSpies;
	float m_spyProb;

	int m_spyPresentNotFound = 0;
	int m_spyFoundLeaderChange = 0;
	int m_spyFoundLeaderStick = 0;
};