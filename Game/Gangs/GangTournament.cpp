#include "GangTournament.h"

#include "Gang.h"
#include "GangGame.h"
#include "../../Utility/FileManager.h"
#include "../../Utility/Utility.h"

#include <iostream>
#include <fstream>
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
	PrintReport(std::cout);

	std::ofstream outFile("GangTournamentReport.txt");
	PrintReport(outFile);
	PrintSpyStatistics(outFile);

}


void GangTournament::MoveWinners() {
	auto iter = m_rankings.begin();
	for (int i = 0; i < m_numberOfWinners; ++i, ++iter) {
		std::string outputFile = m_outputDirectory + "Tournament_" + std::to_string(m_ID) + "_Position_" + std::to_string(i + 1) + fileFormat;
		std::string code = m_gangs[iter->first].GetCode();
		FileMgr->WriteFile(outputFile, code);
	}
}

int GangTournament::GetScore(int gangID) {
	return m_scores[gangID];
}


//TODO: Refactor -> Break into smaller functions
//TODO: Refactor -> This will blow up if ID's are not in order from 0
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

//TODO: Refactor -> Remove magic numbers
void GangTournament::PrintPrisonerPerformance(std::ostream& os) {
	for (int i = 0; i < m_gangs.size(); ++i) {
		
			os << std::setw(12) << std::left << m_gangs[i].GetID();
			os << std::setw(12) << std::left << m_victories[i];
			os << std::setw(12) << std::left << m_draws[i];
			os << std::setw(12) << std::left << (m_gangs.size() - 1) - m_draws[i] - m_victories[i];
			os << std::setw(12) << std::left << m_scores[i] << std::endl;
		}
}

//TODO: Refactor -> Will print incorrectly if ID's are not sequential
void GangTournament::PrintGameResults(std::ostream& os) {
	PrintStarLine(os);
	PrintStarLine(os, true);
	for (int i = 0; i <m_gangs.size(); ++i) {
		for (int j = 0; j <m_gangs.size(); ++j) {
			if (m_results.GetElement(i, j) == WIN) {
				os << "Gang " << i << " beat " << "Gang " << j << std::endl;
			}
			else if (m_results.GetElement(i, j) == LOSE) {
				os << "Gang " << i << " lost to  " << "Gang " << j << std::endl;
			}
			else if (m_results.GetElement(i, j) == DRAW) {
				os << "Gang " << i << " drew with  " << "Gang " << j << std::endl;
			}
		}
	}
	PrintStarLine(os);
	PrintStarLine(os, true);
}

void GangTournament::PrintHeader(std::ostream& os) {
	os << std::setw(12) << std::left << "Gang";
	os << std::setw(12) << std::left << "Victories";
	os << std::setw(12) << std::left << "Draws";
	os << std::setw(12) << std::left << "Losses";
	os << std::setw(12) << std::left << "Score" << std::endl;
}


void GangTournament::PrintIntro(std::ostream& os) {
	os << "Results for Tournament #" << m_ID << std::endl;
	os << "Number of Gangs: " <<m_gangs.size() << std::endl;
	os << "Winner: Gang-" << m_gangs[m_rankings.begin()->first].GetID()
		<< " Score: " << m_scores[m_rankings.begin()->first] << std::endl;
	os << "Winning Strategy: " << std::endl;
	os << m_gangs[m_rankings.begin()->first].GetCode();
	os << std::endl;
}

void GangTournament::PrintReport(std::ostream& os) {
	PrintStarLine(os);
	PrintStarLine(os, true);
	PrintIntro(os);
	PrintHeader(os);
	PrintPrisonerPerformance(os);

	PrintStarLine(os);
	PrintStarLine(os, true);
}

void GangTournament::PrintSpyStatistics(std::ostream& os) {
	os << "Tournament " << m_ID << " Spy Statistics" << std::endl;
	os << "Rounds Played: " << m_iterationsPerGame * factorial(m_gangs.size()) << std::endl;
	os << "Spy Probability: " << m_spyProb << std::endl;
	os << "Spies Found: " << m_spyFoundLeaderChange + m_spyFoundLeaderStick << std::endl;
	os << "Spies Missed:" << m_spyPresentNotFound << std::endl;
	os << "Spies Found After Leader Switch: " << m_spyFoundLeaderChange << std::endl;
	os << "Spies Found After Leader Stick: " << m_spyFoundLeaderStick << std::endl;
}