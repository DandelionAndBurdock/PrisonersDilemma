#include "Tournament.h"



Tournament::Tournament(const std::string& fileDirectory, bool generateStrategies,
	int iterationsPerGame, int numberOfPrisoners,
	int punishmentSentence, int temptationSentence,
	int silentSentence, int suckerSentence) :
	m_iterationsPerGame(iterationsPerGame),
	//m_payoffs = { punishmentSentence, temptationSentence, suckerSentence, silentSentence },
	 //TODO: Generate Sentence structure in one go
	m_numberOfPrisoners(numberOfPrisoners),
	m_createNewStrategies(generateStrategies),
	m_directory(fileDirectory)
{
	LoadPrisoners();
	//m_victories = new int[m_numberOfPrisoners];
	//TODO: Generate 10  stratesgies
	//TODO: Load strategies from file to prisoners
	//TODO: Save best winners 
}

void Tournament::LoadPrisoners() {
	if (m_createNewStrategies) {
		CreateNewStrategies();
	}
	else {
		LoadStrategies();
	}
}

void Tournament::CreateNewStrategies() {
	for (int prisonerID = 0; prisonerID < m_numberOfPrisoners; ++prisonerID) {
		
		std::string strategyFile = m_directory + std::to_string(prisonerID) + std::string(".txt");//TODO:FOrmat
		generator.GenerateStrategy(strategyFile);
		Prisoner p(prisonerID, strategyFile);
		while (!tester.PassesTest(p)) {
			generator.GenerateStrategy(strategyFile);
			p.ChangeStrategy(strategyFile); //TODO: Define assignment operator
		}
		m_prisoners.push_back(p);
	}
}

void Tournament::LoadStrategies() {

}

Tournament::~Tournament()
{
	//delete[] m_victories;
}


bool Tournament::RunTournament() {

	for (auto prisonerA = m_prisoners.begin(); prisonerA != std::prev(m_prisoners.end()); ++prisonerA) {
		for (auto prisonerB = prisonerA + 1; prisonerB != m_prisoners.end(); ++prisonerB) {
			//++m_victories[RunGame(*prisonerA, *prisonerB)];
		}
	}
	return false;
}

int Tournament::RunGame(Prisoner& prisonerA, Prisoner& prisonerB) {
	Game game(prisonerA, prisonerB, m_iterationsPerGame, m_payoffs);
	return game.GetWinner();
}