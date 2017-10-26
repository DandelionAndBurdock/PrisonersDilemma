#include "Tournament.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <numeric> // For std::numeric_limits<int>::max()
#include <iomanip> // For std::setw()


#include "../Utility/FileManager.h"


Tournament::Tournament(int ID, int numberOfPrisoners, bool generateStrategies,
	const std::string& inputFileDirectory, const std::string& outputFileDirectory, std::vector<std::string>& strategyFileNames,
	int numberOfWinners, int iterationsPerGame, 
	Sentence sentences) :
	m_iterationsPerGame(iterationsPerGame),
	m_numberOfPrisoners(numberOfPrisoners),
	m_createNewStrategies(generateStrategies),
	m_inputDirectory(inputFileDirectory),
	m_outputDirectory(outputFileDirectory),
	m_results(Matrix<Result>(numberOfPrisoners)),
	m_gameScores(Matrix<int>(numberOfPrisoners)),
	m_scores(std::vector<int>(numberOfPrisoners, 0)),
	m_victories(std::vector<int>(numberOfPrisoners, 0)),
	m_draws(std::vector<int>(numberOfPrisoners, 0)),
	m_ID(ID),
	m_payoffs(sentences),
	m_numberOfWinners(numberOfWinners), 
	m_strategyFileNames(strategyFileNames)
{
	//Initialise results matrix
	for (int x = 0; x < numberOfPrisoners; ++x)
		for (int y = 0; y < numberOfPrisoners; ++y) {
			m_results.SetElement(x, y, Result::UNFINISHED);
		}

	//Initialise scores matrix
	for (int x = 0; x < numberOfPrisoners; ++x)
		for (int y = 0; y < numberOfPrisoners; ++y) {
			m_gameScores.SetElement(x, y, 0);
		}

	if (m_numberOfWinners > m_numberOfPrisoners) {
		m_numberOfWinners = m_numberOfPrisoners;
	}

	LoadPrisoners();
}



void Tournament::LoadPrisoners() {
	m_prisoners.reserve(m_numberOfPrisoners);
	if (m_createNewStrategies) {
		CreateNewStrategies();
	}
	else {
		LoadStrategies();
	}
}

void Tournament::CreateNewStrategies() {
	for (int prisonerID = 0; prisonerID < m_numberOfPrisoners; ++prisonerID) {
		
		std::string strategyFile = m_inputDirectory + std::to_string(prisonerID) + fileFormat;
		m_generator.GenerateStrategy(strategyFile);
		Prisoner p(prisonerID, strategyFile);
		while (!m_tester.PassesTest(p)) {
			m_generator.GenerateStrategy(strategyFile);
			p.ChangeStrategy(strategyFile); 
		}
		m_prisoners.push_back(p);
	}
}

void Tournament::LoadStrategies() { 
	std::string strategyFile;
	for (int prisonerID = 0; prisonerID < m_numberOfPrisoners; ++prisonerID) {
		if (m_strategyFileNames.empty()) {
			strategyFile = m_inputDirectory + std::to_string(prisonerID) + fileFormat;
		}
		else {
			strategyFile = m_strategyFileNames[prisonerID];
		}
		
		m_prisoners.push_back(Prisoner(prisonerID, strategyFile));
	}
}

Tournament::~Tournament()
{
}

void Tournament::PlayGames() {
	std::vector<std::thread> threadVec;
	for (auto prisonerA = m_prisoners.begin(); prisonerA != std::prev(m_prisoners.end()); ++prisonerA) {
		for (auto prisonerB = prisonerA + 1; prisonerB != m_prisoners.end(); ++prisonerB) {
			RunGame(*prisonerA, *prisonerB);
			//threadVec.push_back(std::thread(std::bind(&Tournament::RunGame, this), pA, pB));
		}
	}

	for (auto& t : threadVec) {
		t.join();
	}
}

void Tournament::RunTournament() {
	PlayGames();
	CalculateRankings();
	MoveWinners(); 
	PrintReport();
}


void Tournament::MoveWinners() {
	auto iter = m_rankings.begin();
	for (int i = 0; i < m_numberOfWinners; ++i, ++iter) {
		std::string outputFile = m_outputDirectory + "Tournament_" + std::to_string(m_ID) + "_Position_" + std::to_string(i + 1) + fileFormat;
		std::string code = m_prisoners[iter->first].GetCode();
		FileManager::Instance()->WriteFile(outputFile, code);
	}
}



// Add one draw for prisoner ID
void Tournament::IncrementDrawCount(int ID) {
	std::lock_guard<std::mutex> guard(m_drawsMutex);
	++m_draws[ID];
}

// Add one victory for prisoner ID
void Tournament::AddToScore(int ID, int deltaScore) {
	std::lock_guard<std::mutex> guard(m_scoresMutex);
	m_scores[ID] += deltaScore;
}

// Add one victory for prisoner ID
int Tournament::GetScore(int ID) {
	std::lock_guard<std::mutex> guard(m_scoresMutex);
	return m_scores[ID];
}

// Add one victory for prisoner ID
int Tournament::GetDrawCount(int ID) {
	std::lock_guard<std::mutex> guard(m_drawsMutex);
	return m_draws[ID];
}


int Tournament::GetVictoryCount(int ID) {
	std::lock_guard<std::mutex> guard(m_victoriesMutex);
	return m_victories[ID];
}

void Tournament::IncrementVictoryCount(int ID) {
	std::lock_guard<std::mutex> guard(m_victoriesMutex);
	++m_victories[ID];
}

void Tournament::SetScore(int ID, int score) {
	std::lock_guard<std::mutex> guard(m_scoresMutex);
	m_scores[ID] = score;
}

//TODO: Refactor Also this will explode if IDs are not sequential
void Tournament::RunGame(Prisoner prisonerA, Prisoner prisonerB) {
	Game game(prisonerA, prisonerB, m_iterationsPerGame, m_payoffs);
	game.Run();
	int winner = game.GetWinner();
	if (winner == prisonerA.GetID()) {
		m_results.SetElement(prisonerA.GetID(), prisonerB.GetID(), WIN);
		m_results.SetElement(prisonerB.GetID(), prisonerA.GetID(), LOSE);
		IncrementVictoryCount(prisonerA.GetID()); 
	}
	else if (winner == prisonerB.GetID()) {
		m_results.SetElement(prisonerA.GetID(), prisonerB.GetID(), LOSE);
		m_results.SetElement(prisonerB.GetID(), prisonerA.GetID(), WIN); 
		IncrementVictoryCount(prisonerB.GetID());
	}
	else {
		m_results.SetElement(prisonerA.GetID(), prisonerB.GetID(), DRAW);
		m_results.SetElement(prisonerB.GetID(), prisonerA.GetID(), DRAW);
		IncrementDrawCount(prisonerA.GetID()); 
		IncrementDrawCount(prisonerB.GetID()); 
	}
	// Update scores
	m_gameScores.SetElement(prisonerA.GetID(), prisonerB.GetID(), prisonerA.GetScore());//TODO: Lock
	m_gameScores.SetElement(prisonerB.GetID(), prisonerA.GetID(), prisonerB.GetScore());//TODO: Lock
}

void Tournament::CalculateRankings() {
	// Calculate scores

	for (int row = 0; row < m_numberOfPrisoners; ++row) {
		if (!m_prisoners[row].HasValidStrategy()) {
			SetScore(row, std::numeric_limits<int>::max());
			continue;
		}
		for (int col = 0; col < m_numberOfPrisoners; ++col) {
			if (row == col) {
				continue;
			}
			if (m_prisoners[col].HasValidStrategy()) {
				AddToScore(row, m_gameScores.GetElement(row, col));
			}
		}
	}

	for (int i = 0; i < m_numberOfPrisoners; ++i) {
		m_rankings.insert(std::make_pair(i, GetScore(i)));
	}
}

//TODO: Magic numbers
void Tournament::PrintPrisonerPerformance() {
	for (int i = 0; i < m_numberOfPrisoners; ++i) {
		if (m_prisoners[i].HasValidStrategy()) {
			std::cout << std::setw(12) << std::left << m_prisoners[i].GetID();
			std::cout << std::setw(12) << std::left << GetVictoryCount(i);//Lock
			std::cout << std::setw(12) << std::left << GetDrawCount(i);
			std::cout << std::setw(12) << std::left << (m_numberOfPrisoners - 1) - GetDrawCount(i) - GetVictoryCount(i); 
			std::cout << std::setw(12) << std::left << GetScore(i) << std::endl;
		}
		else {
			std::cout << std::setw(12) << std::left << m_prisoners[i].GetID();
			std::cout << std::setw(12) << std::left << "DQ";
			std::cout << std::setw(12) << std::left << "DQ";
			std::cout << std::setw(12) << std::left << "DQ";
			std::cout << std::setw(12) << std::left << "DQ" << std::endl;
		}

	}
}

//Helper function: Prints n asertisk characters to the console
void PrintStarLine(bool endLine = false, int n = 40) {
	std::cout << std::endl;
	for (int i = 0; i < n; ++i) {
		std::cout << '*';
	}
	if (endLine) {
		std::cout << std::endl;
	}

}

void Tournament::PrintGameResults() {
	PrintStarLine();
	PrintStarLine(true);
	for (int i = 0; i < m_numberOfPrisoners; ++i) {
		for (int j = 0; j < m_numberOfPrisoners; ++j) {
			if (m_results.GetElement(i, j) == WIN) {
				std::cout << "Prisoner " << i << " beat " << "Prisoner " << j << std::endl;
			}
			else if (m_results.GetElement(i, j) == LOSE) {
				std::cout << "Prisoner " << i << " lost to  " << "Prisoner " << j << std::endl;
			}
			else if (m_results.GetElement(i, j) == DRAW) {
				std::cout << "Prisoner " << i << " drew with  " << "Prisoner " << j << std::endl;
			}
		}
	}
	PrintStarLine();
	PrintStarLine(true);
}

void Tournament::PrintHeader() {
	std::cout << std::setw(12) << std::left << "Prisoner";
	std::cout << std::setw(12) << std::left << "Victories";
	std::cout << std::setw(12) << std::left << "Draws";
	std::cout << std::setw(12) << std::left << "Losses";
	std::cout << std::setw(12) << std::left << "Score" << std::endl;
}


void Tournament::PrintIntro() {
	std::cout << "Results for Tournament #" << m_ID << std::endl;
	std::cout << "Number of Prisoners: " << m_numberOfPrisoners << std::endl;
	std::cout << "Winner: Prisoner-" << m_prisoners[m_rankings.begin()->first].GetID()
		<< " Score: " << m_scores[m_rankings.begin()->first] << std::endl;
	std::cout << "Winning Strategy: " << std::endl;
	std::cout << m_prisoners[m_rankings.begin()->first].GetCode();
	std::cout << std::endl;
}

void Tournament::PrintReport() {
	PrintStarLine();
	PrintStarLine(true);
	PrintIntro();
	PrintHeader();
	PrintPrisonerPerformance();

	PrintStarLine();
	PrintStarLine(true);
}