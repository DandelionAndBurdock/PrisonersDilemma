#pragma once

#include <string>

#include "PrisonersDilemmaGame.h"

class GameManager
{
private:
	enum Selection { TOURNAMENT = 1, CHAMPIONSHIP, GENERATION, TOURNAMENT_OPTIONS, };
public:
	GameManager();
	void Run();
	~GameManager();

private:
	const int maxUserOption = 6;
	const int minUserOption = 1;
	void PrintWelcomeMessage();
	void DisplayOptions();

	int GetUserInput();
	char GetYesOrNo();
	void ResolveInput(int input);


	int m_numberOfPrisoners;
	int m_numberOfTournaments;
	bool m_generateStrategies;
	std::string m_inputFileDirectory;
	std::string m_outputFileDirectory;
	int m_numberOfWinners;
	int m_iterationsPerGame;
	Sentence m_sentences;

	float m_charExpressionProb;	// Probability to generate a character variable expression
	float m_extendArithmeticProb; // Probability to extend an arithmetic expression
	float m_addLineProb;			// Probability to keep adding more lines
	float m_gotoProb;				// Probability of a goto statement to appear at the end of an If
	float m_ifProb;				// Probability of a goto statement to appear at the end of an If


	int m_minimumLineNumber;		// Minimum number of lines that must be generated. Note this can be altered by line numbert
	int m_maximumLineNumber;		// Negative if user does not set it	
	int m_gotoForecast;			// 
};

//TODO: No error reported if try to load strategy but fail