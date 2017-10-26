#include "GangTournament.h"

#include "Gang.h"
#include "GangGame.h"
#include "../../Utility/FileManager.h"

#include <iostream>
#include <iomanip>
//TODO: Rename number of winners, to winnersPerTournament
GangTournament::GangTournament(int ID, std::vector<Gang>& gangs, const std::string& inputDirectory, const std::string& outputDirectory,  bool useSpies,
	float spyProb, int numberIterations, int numberOfWinners) :
	m_scores(std::vector<int>(gangs.size(), 0)),	    // Keeps track of cumulative score
	m_victories(std::vector<int>(gangs.size(), 0)),  // Keeps track of number of victories for each prisoner
	m_draws(std::vector<int>(gangs.size(), 0)),      // Keeps track of number of draws for each prisoner
	m_ID(ID),
	m_results(Matrix<Result>(gangs.size())),
	m_gameScores(Matrix<int>(gangs.size())),
	m_gangs(gangs),
	m_numberOfWinners(numberOfWinners),
	m_iterationsPerGame(numberIterations),
	m_useSpies(useSpies),
	m_spyProb(spyProb)
{
	int numGangs = gangs.size();

	//Initialise results matrix
	for (int x = 0; x < numGangs; ++x)
		for (int y = 0; y < numGangs; ++y) {
			m_results.SetElement(x, y, Result::UNFINISHED);
		}

	//Initialise scores matrix
	for (int x = 0; x < numGangs; ++x)
		for (int y = 0; y < numGangs; ++y) {
			m_gameScores.SetElement(x, y, 0);
		}

	if (m_numberOfWinners > numGangs) {
		m_numberOfWinners = numGangs;
	}

	m_inputDirectory = inputDirectory;
	m_outputDirectory = outputDirectory;
	GangSentence m_payoffs = GangSentence();
}


GangTournament::~GangTournament()
{
}


void GangTournament::PlayGames() {
	for (auto gangA = m_gangs.begin(); gangA != std::prev(m_gangs.end()); ++gangA) {
		for (auto gangB = gangA + 1; gangB != m_gangs.end(); ++gangB) {
			RunGame(*gangA, *gangB);
		}
	}
}

void GangTournament::RunTournament() {
	PlayGames();
	CalculateRankings();
	MoveWinners();
	PrintReport();
}


void GangTournament::MoveWinners() {
	auto iter = m_rankings.begin();
	for (int i = 0; i < m_numberOfWinners; ++i, ++iter) {
		std::string outputFile = m_outputDirectory + "Tournament_" + std::to_string(m_ID) + "_Position_" + std::to_string(i + 1) + fileFormat;
		std::string code = m_gangs[iter->first].GetCode();
		FileManager::Instance()->WriteFile(outputFile, code);
	}
}

int GangTournament::GetScore(int gangID) {
	return m_scores[gangID];
}


//TODO: Refactor also this will blow up -- quick fix add a check
void GangTournament::RunGame(Gang& gangA, Gang& gangB) {
	GangGame game(&gangA, &gangB, m_spyProb, m_useSpies, m_iterationsPerGame);
	game.Run();
 
	int winner = game.GetWinner();

	if (winner == gangA.GetID()) {
		m_results.SetElement(gangA.GetID(), gangB.GetID(), WIN);
		m_results.SetElement(gangB.GetID(), gangA.GetID(), LOSE);
		m_victories[gangA.GetID()]++;
	}
	else if (winner == gangB.GetID()) {
		m_results.SetElement(gangA.GetID(), gangB.GetID(), LOSE);
		m_results.SetElement(gangB.GetID(), gangA.GetID(), WIN);
		m_victories[gangB.GetID()]++;
	}
	else {
		m_results.SetElement(gangA.GetID(), gangB.GetID(), DRAW);
		m_results.SetElement(gangB.GetID(), gangA.GetID(), DRAW);
		m_draws[gangA.GetID()]++;
		m_draws[gangB.GetID()]++;
	}
	// Update scores
	m_gameScores.SetElement(gangA.GetID(), gangB.GetID(), gangA.GetScore());
	m_gameScores.SetElement(gangB.GetID(), gangA.GetID(), gangB.GetScore());

	// Update spy statistics
	m_spyPresentNotFound += game.GetSpyMisses();
	m_spyFoundLeaderChange += game.GetSpyChange();
	m_spyFoundLeaderStick += game.GetSpyStick();
}

void GangTournament::CalculateRankings() {
	// Calculate scores

	for (int row = 0; row < m_gangs.size(); ++row) {
		for (int col = 0; col < m_gangs.size(); ++col) {
			if (row == col) {
				continue;
			}
				m_scores[row] += m_gameScores.GetElement(row, col);
		}
	}

	for (int i = 0; i < m_gangs.size(); ++i) {
		m_rankings.insert(std::make_pair(i, m_scores[i]));
	}
}

//TODO: Magic numbers
void GangTournament::PrintPrisonerPerformance() {
	for (int i = 0; i < m_gangs.size(); ++i) {
		
			std::cout << std::setw(12) << std::left << m_gangs[i].GetID();
			std::cout << std::setw(12) << std::left << m_victories[i];
			std::cout << std::setw(12) << std::left << m_draws[i];
			std::cout << std::setw(12) << std::left << (m_gangs.size() - 1) - m_draws[i] - m_victories[i];
			std::cout << std::setw(12) << std::left << m_scores[i] << std::endl;
		}
}

//TODO: Move this to a header
void PrintStarLine(bool endLine = false, int n = 40);


// TODO: Says prisoner i but should say prisoner[i].GetID()
void GangTournament::PrintGameResults() {
	PrintStarLine();
	PrintStarLine(true);
	for (int i = 0; i <m_gangs.size(); ++i) {
		for (int j = 0; j <m_gangs.size(); ++j) {
			if (m_results.GetElement(i, j) == WIN) {
				std::cout << "Gang " << i << " beat " << "Gang " << j << std::endl;
			}
			else if (m_results.GetElement(i, j) == LOSE) {
				std::cout << "Gang " << i << " lost to  " << "Gang " << j << std::endl;
			}
			else if (m_results.GetElement(i, j) == DRAW) {
				std::cout << "Gang " << i << " drew with  " << "Gang " << j << std::endl;
			}
		}
	}
	PrintStarLine();
	PrintStarLine(true);
}

void GangTournament::PrintHeader() {
	std::cout << std::setw(12) << std::left << "Gang";
	std::cout << std::setw(12) << std::left << "Victories";
	std::cout << std::setw(12) << std::left << "Draws";
	std::cout << std::setw(12) << std::left << "Losses";
	std::cout << std::setw(12) << std::left << "Score" << std::endl;
}


void GangTournament::PrintIntro() {
	std::cout << "Results for Tournament #" << m_ID << std::endl;
	std::cout << "Number of Gangs: " <<m_gangs.size() << std::endl;
	std::cout << "Winner: Gang-" << m_gangs[m_rankings.begin()->first].GetID()
		<< " Score: " << m_scores[m_rankings.begin()->first] << std::endl;
	std::cout << "Winning Strategy: " << std::endl;
	std::cout << m_gangs[m_rankings.begin()->first].GetCode();
	std::cout << std::endl;
}

void GangTournament::PrintReport() {
	PrintStarLine();
	PrintStarLine(true);
	PrintIntro();
	PrintHeader();
	PrintPrisonerPerformance();

	PrintStarLine();
	PrintStarLine(true);
}

//TODO: Move to utility function
int factorial(int n) {
	if (n == 1) {
		return 1;
	}
	else {
		return n * factorial(n- 1);
	}
}

void GangTournament::PrintSpyStatistics() {
	std::cout << "Tournament " << m_ID << " Spy Statistics" << std::endl;
	std::cout << "Rounds Played: " << m_iterationsPerGame * factorial(m_gangs.size()) << std::endl;
	std::cout << "Spy Probability: " << m_spyProb << std::endl;
	std::cout << "Spies Found: " << m_spyFoundLeaderChange + m_spyFoundLeaderStick << std::endl;
	std::cout << "Spies Missed:" << m_spyPresentNotFound << std::endl;
	std::cout << "Spies Found After Leader Switch: " << m_spyFoundLeaderChange << std::endl;
	std::cout << "Spies Found After Leader Stick: " << m_spyFoundLeaderStick << std::endl;
}