#include "Competition.h"


Competition::Competition(int numberOfTournaments, int numberOfPrisoners, int numberOfWinners,
	bool generateStrategies, int iterationsPerGame, std::string inputDirectory, std::string outputDirectory,
	Sentence sentence )   :
	m_numberOfTournaments(numberOfTournaments),
	m_numberOfPrisoners(numberOfPrisoners),
	m_numberOfWinners(numberOfWinners),
	m_iterationsPerGame(iterationsPerGame),
	m_sentence(sentence),
	m_inputDirectory(inputDirectory),
	m_outputDirectory(outputDirectory),
	m_championTournament(nullptr)
{
	// Create tournaments for first round
	for (int ID = 1; ID <= numberOfTournaments; ++ID) {
		m_tournaments.push_back(new Tournament(ID, m_numberOfPrisoners, generateStrategies, m_inputDirectory, m_outputDirectory,
			std::vector<std::string>(), m_numberOfWinners, m_iterationsPerGame, m_sentence));
	}

}


Competition::~Competition()
{
	for (Tournament* ptr : m_tournaments) {
		delete ptr;
	}
	if (m_championTournament) {
		delete m_championTournament;
	}

}

void Competition::RunCompetition() {
	// Run each tournament indiviudally
	for (Tournament* &tournament : m_tournaments) {
		tournament->RunTournament();
	}

	// Run champions of champions tournament
	//TODO: Refactor
	 //Calculate file names
	std::vector<std::string> filenames;
	for (int ID = 1; ID <= m_numberOfTournaments; ++ID) {
		for (int position = 1; position <= m_numberOfWinners; ++position) {
			filenames.push_back(defaultOutputDir + "Tournament_" + std::to_string(ID) + "_Position_" + std::to_string(position) + fileFormat);
		}
	}

	int numberOfContenders = m_numberOfTournaments * m_numberOfWinners;

	m_championTournament = new Tournament(m_numberOfTournaments + 1, numberOfContenders, false, defaultOutputDir, defaultOutputDir + "Champions//",
		filenames, m_numberOfWinners, m_iterationsPerGame, m_sentence);
	if (m_championTournament) {
		m_championTournament->RunTournament();
	}
	

}

void Competition::PrintGameResults() const {
	if (m_championTournament) {
		m_championTournament->PrintGameResults();
	}
}