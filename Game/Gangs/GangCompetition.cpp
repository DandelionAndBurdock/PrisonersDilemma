#include "GangCompetition.h"

#include "Gang.h"
#include "GangTournament.h"
#include "../PrisonersDilemmaGame.h"

#include "../../Utility/FileManager.h"
#include <sstream>
#include <iostream>

GangCompetition::GangCompetition(int numberOfTournaments, int numberOfGangs, bool useSpies, float spyProb, int numberOfWinners,
	bool generateStrategies, int iterationsPerGames, std::string inputDirectory,
	std::string outputDirectory,
	GangSentence sentence)
{
	m_numberOfTournaments = numberOfTournaments;
	m_numberOfWinners = numberOfWinners;
	m_outputDirectory = outputDirectory;
	m_inputDirectory = inputDirectory;
	m_iterationsPerGame = iterationsPerGames;
	m_numberOfGangs = numberOfGangs;
	m_useSpies = useSpies;
	m_spyProb = spyProb;

	PrepareFirstRound();
}


GangCompetition::~GangCompetition()
{
	for (GangTournament* ptr : m_tournaments) {
		delete ptr;
	}
	if (m_championTournament) {
		delete m_championTournament;
	}

}

void GangCompetition::RunCompetition() {
	RunFirstRound();
	GetFileNames();
	SplitGangStrategy();
	RunFinalRound();
}

void GangCompetition::PrepareFirstRound() {
	const int PRISONERS_PER_GANG = 5;
	for (int ID = 1; ID <= m_numberOfTournaments; ++ID) {
		std::vector<Gang> gangs;
		for (int i = 0; i < m_numberOfGangs; ++i) {
			gangs.push_back(Gang(i, PRISONERS_PER_GANG));
		}
		m_tournaments.push_back(new GangTournament(ID, gangs, m_inputDirectory, m_outputDirectory, m_useSpies,
			m_spyProb, m_iterationsPerGame, m_numberOfWinners));
	}
}
void GangCompetition::RunFirstRound() {
	// Run each tournament indiviudally
	for (GangTournament* &tournament : m_tournaments) {
		tournament->RunTournament();
	}
}
void GangCompetition::GetFileNames() {
	for (int ID = 1; ID <= m_numberOfTournaments; ++ID) {
		for (int position = 1; position <= m_numberOfWinners; ++position) {
			m_filenames.push_back(m_outputDirectory + "Tournament_" + std::to_string(ID) +
				"_Position_" + std::to_string(position) + fileFormat);
		}
	}
}

//TODO: Refactor->Remove magic numbers 
//TODO: Restructure for clarity -> Seprate file I/O, string splitting and 
// gang creation into seperate functions
//TODO: Will break with more than 10 prisoners
void GangCompetition::SplitGangStrategy() {

	std::string temp;
	std::string code;

	int id = 0;
	for (auto& file : m_filenames) {
		std::string source = FileManager::Instance()->ReadFile(file);
		std::istringstream ss(source);
		while (std::getline(ss, temp)) {
			if (temp[0] != '*') {
				code += temp;
				code += "\n";
			}
			else {
				code += '*';
			}
		}
		std::vector<std::string> gangFiles;
		for (int i = 0; i < 5; ++i) { // Break file into one string for each prisoner
			int start = 0;
			int end = code.find_first_of('*', start + 1);

			std::string gangCode = code.substr(start + 1, end - 1);
			std::string remainingCode;

			if (end != std::string::npos) {
				remainingCode = code.substr(end);
			}
			code = remainingCode;
			start = end;

			// Write out strategies to individual files
			std::string outputFile = m_outputDirectory + std::to_string(i) + "Winner.txt";
			FileManager::Instance()->WriteFile(outputFile, gangCode);

			gangFiles.push_back(outputFile);
		}
		m_gangs.push_back(Gang(id++, gangFiles));
	}
}

void GangCompetition::RunFinalRound() {
	m_championTournament = new GangTournament(m_numberOfTournaments + 1, m_gangs, m_outputDirectory, m_outputDirectory + "Champions//",
		m_useSpies, m_spyProb, m_iterationsPerGame, m_numberOfWinners);

	if (m_championTournament) {
		m_championTournament->RunTournament();
	}
}


void GangCompetition::PrintGameResults() {
	if (m_championTournament) {
		m_championTournament->PrintGameResults(std::cout);
	}
}

void GangCompetition::PrintSpyStatistics() {
	if (m_championTournament) {
		m_championTournament->PrintSpyStatistics(std::cout);
	}
}