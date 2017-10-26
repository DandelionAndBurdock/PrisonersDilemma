#include "GangCompetition.h"

#include "Gang.h"
#include "GangTournament.h"
#include "PrisonersDilemmaGame.h"

#include "../Utility/FileManager.h"
#include <sstream>

GangCompetition::GangCompetition(int numberOfTournaments, int numberOfGangs, int numberOfWinners,
	bool generateStrategies, int iterationsPerGames, std::string inputDirectory,
	std::string outputDirectory,
	GangSentence sentence)
{
	m_numberOfTournaments = numberOfTournaments;
	m_numberOfWinners = numberOfWinners;
	m_outputDirectory = outputDirectory;
	m_inputDirectory = inputDirectory;
	m_iterationsPerGame = iterationsPerGames;
	//TODO: Refactor
	for (int ID = 1; ID <= numberOfTournaments; ++ID) {
		// Make some gangs
		std::vector<Gang> gangs;
		for (int i = 0; i < numberOfGangs; ++i) {
			gangs.push_back(Gang(i, 5)); //TODO: Magic number
		}
		m_tournaments.push_back(new GangTournament(ID, gangs, inputDirectory, outputDirectory, false, 0.0f, iterationsPerGames, m_numberOfWinners ));

	
	}
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
	// Run each tournament indiviudally
	for (GangTournament* &tournament : m_tournaments) {
		tournament->RunTournament();
	}

	// Run champions of champions tournament
	//TODO: Refactor
	//Calculate file names
	std::vector<std::string> filenames;
	for (int ID = 1; ID <= m_numberOfTournaments; ++ID) {
		for (int position = 1; position <= m_numberOfWinners; ++position) {
			filenames.push_back(m_outputDirectory + "Tournament_" + std::to_string(ID) + "_Position_" + std::to_string(position) + fileFormat);
		}
	}

	int numberOfContenders = m_numberOfTournaments * m_numberOfWinners;
	std::vector<Gang> gangs;
	std::string temp;
	std::string code;

	int id = 0;
	for (auto& file : filenames) {
		
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

		//TODO: Will break if more than 10 prisoners
		std::vector<std::string> gangFiles;
		for (int i = 0; i < 5; ++i) {
			int start = 0;
			int end = code.find_first_of('*',start + 1);
		std::string gangCode = code.substr(start + 1, end -	1);
		std::string remainingCode;
		if (end != std::string::npos) {
			remainingCode = code.substr(end);
		}
		
	
		code = remainingCode;
		start = end;
			
			std::string outputFile = m_outputDirectory + std::to_string(i) + "Winner.txt";
			FileManager::Instance()->WriteFile(outputFile, gangCode);

			gangFiles.push_back(outputFile);
		}
		gangs.push_back(Gang(id++, gangFiles));
	}

	m_championTournament = new GangTournament(m_numberOfTournaments + 1, gangs, m_outputDirectory, m_outputDirectory + "Champions//",
		false, 0.0f, m_iterationsPerGame, m_numberOfWinners);

	if (m_championTournament) {
		m_championTournament->RunTournament();
	}


}

void GangCompetition::PrintGameResults() {
	if (m_championTournament) {
		m_championTournament->PrintGameResults();
	}
}