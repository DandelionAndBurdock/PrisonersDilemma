#pragma once

#include <string>
//TODO: Put in namespace
enum ActionType { BETRAY, SILENCE, GOTO, NEXT_LINE, INVALID_ACTION };//TODO: Comment
struct Action{
	Action(ActionType a, int line = -1) :
		m_action(a), m_line(line){}

	ActionType  m_action;
	int		m_line;		// If GOTO holds the line
};


struct Sentence {
	Sentence(int punish = 4, int tempt = 0, int silent = 2, int sucker = 5) :
		m_punishment(punish), m_temptation(tempt),
		m_silent(silent), m_sucker(sucker)
	{}
	int m_punishment;	// Sentence added when a prisoner betrays and oppenent betrays
	int m_temptation;	// Sentence added when a prisoner betrays and opponent is silent
	int m_silent;		// Sentence added when a prisoner is silent and opponent is silent
	int m_sucker;		// Sentence added when a prisoner is silent and opponent betrays
};

struct GangSentence : public Sentence
{
	GangSentence(int mostBetrayed = 6, int leastBetrayed = 5, int sameBetrayed = 2) :
		Sentence(8, 0, 4, 10), m_mostBetrayed(mostBetrayed), m_leastBetrayed(leastBetrayed), m_sameBetrayed(sameBetrayed)
	{}
	int m_mostBetrayed;
	int m_leastBetrayed; //TODO: Make floats
	int m_sameBetrayed;

	int m_bothDiscoverSpy = 6;
	int m_changeDiscoverSpy = 2;
	int m_stickDiscoverSpy = 0;
	int m_spyUnmasked = 5;
};

// Default values
// Tournaments
const int defaultTournaments = 3;												  // Default number of tournaments to run in a competition
const int defaultWinners = 3;													  // Default number of strategies from each tournament which go through to the championship
const std::string defaultInputDir = "Tournaments//";							  // Default folder to read in strategy files
const std::string defaultOutputDir = defaultInputDir + std::string("Winners//");  // Default sub-folder to output winning tournament strategies and tournament report
const std::string defaultGangInDir = "GangTournaments//";							  // Default folder to read in strategy files
const std::string defaultGangOutDir = defaultGangInDir + std::string("Winners//");  // Default sub-folder to output winning tournament strategies and tournament report
const bool defaultGenStrategies = true;										  // Default behaviour for generating strategies
const int defaultIterations = 200;												  // Default number of iterations per game
const int defaultPrisoners = 10;	
const int defaultGangs = 3; // Default number of gangs per tournament
const std::string fileFormat = ".txt";											  // File format for saving and loading strategies

																				  //TODO: Replace with leaderboard class, vector and sort function
struct Comparison
{
	bool operator ()(const std::pair<int, int>& a, const std::pair<int, int>& b) { // Will compare two pairs of pair<ID, Victories> want to sort in ascending order number of victories
		if (a.second != b.second) {
			return a.second < b.second;
		}
		else {
			return a.first < b.first;
		}
	}
};