#include "Tournament.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <utility>

#include "Utility/FileManager.h"

Tournament::Tournament(int ID, const std::string& fileDirectory, bool generateStrategies,
	int iterationsPerGame, int numberOfPrisoners,
	int punishmentSentence, int temptationSentence,
	int silentSentence, int suckerSentence) :
	m_iterationsPerGame(iterationsPerGame),
	//m_payoffs = { punishmentSentence, temptationSentence, suckerSentence, silentSentence },
	 //TODO: Generate Sentence structure in one go
	m_numberOfPrisoners(numberOfPrisoners),
	m_createNewStrategies(generateStrategies),
	m_directory(fileDirectory),
	m_results(Matrix<Result>(numberOfPrisoners)),
	m_victories(std::vector<int>(numberOfPrisoners, 0)),
	m_ID(ID)
{
	//m_results = Matrix<Result>(numberOfPrisoners);//TODO: Why can't I get this in the initializer list
	for (int x = 0; x < numberOfPrisoners; ++x)
		for (int y = 0; y < numberOfPrisoners; ++y) {
			m_results.SetElement(x, y, Result::UNFINISHED);
		}

	

	LoadPrisoners();

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

void Tournament::LoadStrategies() { //TODO: Possibly doesn't need to be a seperate function
	for (int prisonerID = 0; prisonerID < m_numberOfPrisoners; ++prisonerID) {
		std::string strategyFile = m_directory + std::to_string(prisonerID) + std::string(".txt");//TODO:FOrmat
		Prisoner p(prisonerID, strategyFile);
		m_prisoners.push_back(p);
	}
}

Tournament::~Tournament()
{
}

void Tournament::PlayGames() {
	for (auto prisonerA = m_prisoners.begin(); prisonerA != std::prev(m_prisoners.end()); ++prisonerA) {
		for (auto prisonerB = prisonerA + 1; prisonerB != m_prisoners.end(); ++prisonerB) {
			RunGame(*prisonerA, *prisonerB);
		}
	}
}

void Tournament::RunTournament() {
	PlayGames();
	MoveWinners(3); //TOOD: Magic numbers
}

void Tournament::MoveWinners(int n) {
	struct Comparison
	{
		bool operator ()(const std::pair<int, int>& a, const std::pair<int, int>& b){ // Will compare two pairs of pair<ID, Victories> want to sort in ascending order number of victories
			return a.second > b.second;
		}
	};
	std::set<std::pair<int, int>, Comparison> rankings; // Will hold pair of victories/ ID
	for (int i = 0; i < m_numberOfPrisoners; ++i) {
		rankings.insert(std::make_pair(i, m_victories[i]));
	}

	auto iter = rankings.begin();
	//TODO: Assert n < numberOfPrisoners
	for (int i = 0; i < n; ++i) {
		std::string outputFile = m_directory + "//Winners//Tournament_" + std::to_string(m_ID) + "_Position_" + std::to_string(i + 1) + std::string(".txt");
		std::string code = m_prisoners[iter->first].GetCode();
		FileManager::Instance()->WriteFile(outputFile, code);
	}
	

}

int Tournament::RunGame(Prisoner& prisonerA, Prisoner& prisonerB) {//TODO: Handle draw -> CAn return negative number if equal
	Game game(prisonerA, prisonerB, m_iterationsPerGame, m_payoffs);
	int winner = game.GetWinner();
	if (winner == prisonerA.GetID()) {
		m_results.SetElement(prisonerA.GetID(), prisonerB.GetID(), WIN);
		m_results.SetElement(prisonerB.GetID(), prisonerA.GetID(), LOSE);
		m_victories[prisonerA.GetID()]++;
	}
	else {
		m_results.SetElement(prisonerA.GetID(), prisonerB.GetID(), LOSE);
		m_results.SetElement(prisonerB.GetID(), prisonerA.GetID(), WIN); //TODO: Is there a smart way to do this?
		m_victories[prisonerB.GetID()]++;
	}
	return winner;
}

void Tournament::CalculateRankings() {
	const int WIN_POINTS = 3;
	const int DRAW_POINTS = 1;
	const int LOSS_POINTS = 0;
	for (int i = 0; i < m_numberOfPrisoners; ++i) {
		for (int j = 0; j < m_numberOfPrisoners; ++j) {
			if (m_results.GetElement(i, j) == WIN) {
				std::cout << "Prisoner " << i << " beat " << " Prisoner " << j << std::endl;
			}
			else if (m_results.GetElement(i, j) == LOSE) {
				std::cout << "Prisoner " << i << " lost to  " << " Prisoner " << j << std::endl;
			}
		}
	}

	for (int i = 0; i < m_numberOfPrisoners; ++i) {
		std::cout << "Prisoner " << i << " has " << m_victories[i] << " victories" << std::endl;
	}
}

