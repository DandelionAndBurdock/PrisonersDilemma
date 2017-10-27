#pragma once

// Standard Includes
#include <set>
#include <vector>

#include "../../Utility/Matrix.h"

#include "../PrisonersDilemmaGame.h"

#include "Gang.h"

class GangTournament
{
	enum Result { WIN, LOSE, DRAW, UNFINISHED }; // Possible game outcomes
public:
	// Constructor
	GangTournament(int ID, std::vector<Gang>& gangs, const std::string& inputDirectory = defaultGangInDir, 
		const std::string& outputDirectory = defaultGangOutDir, bool useSpies = false,
		float spyProb = 0.0f, int numberIterations = 200, int numberOfWinners = 2);
	~GangTournament();

	// Plays games of tournament, saves winning strategies and generates output
	void RunTournament();

	// Displays which prisoner beat which other prisoner
	void PrintGameResults(std::ostream& os);

	// Displays statistics related to spies
	void PrintSpyStatistics(std::ostream& os);

	int GetScore(int gandID);
private:
	// Creates a map from the gang ID to score ordered by highest score
	void CalculateRankings();

	// Runs all games in the tournament
	void PlayGames();

	// Simulates a game for prisoner A and prisoner B and returns the ID of the winner
	void RunGame(Gang& gangA, Gang& gangB);

	// Copies top m_numberOfWinners strategies to the output directory 
	void MoveWinners();

	// Generate statistics for the user about the tournament
	void PrintReport(std::ostream& os);

	//Helper functions for PrintReport()
	void PrintIntro(std::ostream& os);
	void PrintHeader(std::ostream& os);
	void PrintPrisonerPerformance(std::ostream& os);


	std::vector<Gang>	  m_gangs;		// List or prisoners in the tournament
	Matrix<Result>        m_results;    // Keep track of outcome of game for each pair of prisoners
	Matrix<int>			  m_gameScores; // Keep track of scores in each game
	std::vector<int>      m_scores;	    // Keeps track of cumulative score
	std::vector<int>      m_victories;  // Keeps track of number of victories for each prisoner
	std::vector<int>      m_draws;      // Keeps track of number of draws for each prisoner

	int  m_iterationsPerGame;			// Number of iterations for each game in the tournament
	int  m_numberOfWinners;				// Number of winning strategies to save in the output directory

	int m_ID;							// Identifaction number for this tournament

	std::string m_inputDirectory;		// Folder to read strategies from (or generate new strategies too)
	std::string m_outputDirectory;		// Folder to write winning strategies and statistics
	GangSentence    m_payoffs;			    // Contains the score changes for all possible game outcomes

	std::set<std::pair<int, int>, Comparison> m_rankings; // Will hold pair of victories/ ID 

	bool m_useSpies;				// True if spies are active in this tournament
	float m_spyProb;				// Probability for a spy to be present in a game iteration

	int m_spyPresentNotFound = 0;		// number of times a spy was present but not detected
	int m_spyFoundLeaderChange = 0;		// number of times a spy was present and detected by a leader who changed initial guess
	int m_spyFoundLeaderStick = 0;		// number of times a spy was present and detected by a leader who stuck to initial guess
};