// Class: Competition
// Description: Handles competitions (a tournament of tournaments)
// Author: Philip Jones
// Date: 17/10/2017
#pragma once
#include <string>
#include <vector>

#include "Tournament.h"
#include "PrisonersDilemmaGame.h"

class Competition
{
public:
	// Constructor
	Competition(int numberOfTournaments = defaultTournaments, int numberOfPrisoners = defaultPrisoners, int numberOfWinners = defaultWinners,
		bool generateStrategies = defaultGenStrategies, int iterationsPerGame = defaultIterations, std::string inputDirectory = defaultInputDir,
	std::string outputDirectory = defaultOutputDir, 
		Sentence sentence = Sentence());
	// Destructor
	~Competition();

	// Simulates a 'numberOfTournaments' tournaments each witn 'numberOfPrisoners' prisoners. At the 
	// conclusion of each tournament the best 'numberOfWinners' strategies are written to the output directory.
	// These best strategies then compete against each other in one final super tournament.
	void RunCompetition();

	// Displays results to the console
	void PrintGameResults() const;
private:
	// Runs first round of tournaments
	void RunFirstRound();
	// Create vector of strings containing strategy filepaths for finalists
	void GetFileNames();
	// Run final tournament of first round winners
	void RunFinalRound();

	// Vector of pointers to the initial first round tournaments
	std::vector<Tournament*> m_tournaments;

	// Holds filenames of first round winners
	std::vector<std::string> m_filenames;

	int m_numberOfTournaments;			// Number of first round tournaments to run
	int m_numberOfPrisoners;			// Number of prisoners in each first round tournament
	int m_numberOfWinners;				// The number of best strategies from each first round tournament which progress to the final
	int m_iterationsPerGame;			// The number of game iterations for each game in the tournament

	std::string m_inputDirectory;		// Directory to load prisoner strategies from
	std::string m_outputDirectory;		// Directory to write best first round strategies to

	Sentence m_sentence;				// Contains punishment parameters for the game

	Tournament* m_championTournament;	 // Pointer to the final "super" tournament


};

