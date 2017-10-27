// Class: Competition
// Description: Handles competition (a tournament of tournaments)
// Author: Philip Jones
// Date: 17/10/2017
#pragma once
#include <string>
#include <vector>

class GangTournament;

#include "../PrisonersDilemmaGame.h"

#include "Gang.h"

class GangCompetition
{
public:
	GangCompetition(int numberOfTournaments = defaultTournaments, int numberOfGangs = defaultGangs, bool useSpies = false, 
		float spyProb = defaultSpyProb, int numberOfWinners = defaultWinners,
		bool generateStrategies = defaultGenStrategies, int iterationsPerGame = defaultIterations, std::string inputDirectory = defaultGangInDir,
		std::string outputDirectory = defaultGangOutDir,
		GangSentence sentence = GangSentence());

	~GangCompetition();

	// Generates gangs to compete in several tournaments. The winners of these tournament
	// progress to a final 'super' tournament of champions
	void RunCompetition();

	// Print score and game breakdown for each gang
	void PrintGameResults();

	// Print statistics related to spy activity
	void PrintSpyStatistics();
private:
	// Generate gangs to compete in the first round 
	void PrepareFirstRound();
	// Runs first round of tournaments
	void RunFirstRound();
	// Create vector of strings containing strategy filepaths for finalists
	void GetFileNames();
	// Break up combined gang strategy into individual strategy files
	void SplitGangStrategy();
	// Run final tournament of first round winners
	void RunFinalRound();

	// Vector of gangs in the final
	std::vector<Gang> m_gangs;

	// Holds filenames of first round winners
	std::vector<std::string> m_filenames;

	// First round tournaments
	std::vector<GangTournament*> m_tournaments;

	int m_numberOfTournaments;	// Number of tournaments per round 
	int m_numberOfGangs;		// Number of gangs per tournament
	int m_numberOfWinners;		// Number of gangs in the first round who advance to the final
	int m_iterationsPerGame;	// Number of iterations per game
	bool m_useSpies;			// Are spies active in this tournament
	float m_spyProb;				// Probability to find a spy

	std::string m_inputDirectory;	// Directory to read files from
	std::string m_outputDirectory;	// Directory to write winners to

	GangSentence m_sentence;		// Parameters for sentencing rules

	GangTournament* m_championTournament; // Final tournament of first round winners
};




