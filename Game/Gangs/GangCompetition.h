// Class: Competition
// Description: Handles competition (a tournament of tournaments)
// Author: Philip Jones
// Date: 17/10/2017
#pragma once
#include <string>
#include <vector>

class GangTournament;

#include "../PrisonersDilemmaGame.h"

class GangCompetition
{
public:
	GangCompetition(int numberOfTournaments = defaultTournaments, int numberOfGangs = defaultGangs, int numberOfWinners = defaultWinners,
		bool generateStrategies = defaultGenStrategies, int iterationsPerGame = defaultIterations, std::string inputDirectory = defaultGangInDir,
		std::string outputDirectory = defaultGangOutDir,
		GangSentence sentence = GangSentence());

	~GangCompetition();

	void RunCompetition();
	void PrintGameResults();
private:
	std::vector<GangTournament*> m_tournaments;
	std::string m_directory;

	int m_numberOfTournaments;
	int m_numberOfPrisoners;
	int m_numberOfWinners;
	int m_iterationsPerGame;

	std::string m_inputDirectory;
	std::string m_outputDirectory;

	GangSentence m_sentence;

	GangTournament* m_championTournament;
};




