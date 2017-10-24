// Class: Competition
// Description: Handles competition (a tournament of tournaments)
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
	Competition(int numberOfTournaments = defaultTournaments, int numberOfPrisoners = defaultPrisoners, int numberOfWinners = defaultWinners,
		bool generateStrategies = defaultGenStrategies, int iterationsPerGame = defaultIterations, std::string inputDirectory = defaultInputDir,
	std::string outputDirectory = defaultOutputDir, 
		Sentence sentence = Sentence());
	~Competition();

	void RunCompetition();
	void PrintGameResults();
private:
	std::vector<Tournament*> m_tournaments;
	std::string m_directory;

	int m_numberOfTournaments;
	int m_numberOfPrisoners;
	int m_numberOfWinners;
	int m_iterationsPerGame;

	std::string m_inputDirectory;
	std::string m_outputDirectory;

	Sentence m_sentence;

	Tournament* m_championTournament;
};

