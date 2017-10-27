// Class: GameManager
// Description: Workhorse class that handles triggers tournaments and championships
// based on user input
// Author: Philip Jones
// Date: 19/10/2017

#pragma once

#include <string>

#include "PrisonersDilemmaGame.h"

class GameManager
{
private:
	enum Selection { TOURNAMENT = 1, CHAMPIONSHIP, GENERATION, TOURNAMENT_OPTIONS, QUIT}; // Possible user selection options
public:
	GameManager();
	void Run();
	~GameManager();

private:
	// User Input

	int GetUserInput();					// Prompts user for an integer between minUserOption and maxUserOption and validates input
	float GetUserFloat();				// Prompts user for a float and validates is a valid number
	int GetUserInt();					// Prompts user for a integer and validates is a valid number
	char GetYesOrNo();					// Prompts user for a y or n

										// Gang Parameters

	bool m_gangs;						// True if in gang vs gang mode false if in prisoner vs prisoner mode
	int m_numGangs;						// Number of gangs in a GangTournament
	int m_numGangMembers;				// Number of prisoners in a gang
	bool m_spies;						// True if spies are active
	float m_spyProb;					// Probability for a spy to be selected
	bool m_leaderChange;				// True if leader changes initial guess

										// Tournament Parameters

	int m_numberOfPrisoners;			// Number of prisoners in a prisoner tournament
	int m_numberOfTournaments;			// Number of tournaments in a championship
	bool m_generateStrategies;			// True if strategies are randomly generated
	std::string m_inputFileDirectory;	// Directory to load strategy files
	std::string m_outputFileDirectory;	// Directory to load output files
	int m_numberOfWinners;				// Number of strategies that move onto final round of championship
	int m_iterationsPerGame;			// Number of iterations per game
	Sentence m_sentences;				// Punishment parameters for game

										// Strategy Generation Parameters

	float m_charExpressionProb;	// Probability to generate a character variable expression
	float m_extendArithmeticProb; // Probability to extend an arithmetic expression
	float m_addLineProb;			// Probability to keep adding more lines
	float m_gotoProb;				// Probability of a goto statement to appear at the end of an If
	float m_ifProb;				// Probability of a goto statement to appear at the end of an If


	int m_minimumLineNumber;		// Minimum number of lines that must be generated. Note this can be altered by line numbert
	int m_maximumLineNumber;		// Negative if user does not set it	
	int m_gotoForecast;			//  Number of lines a goto statement may jump ahead


	
	// Handle parameter setting
	void SetGenerationOptions();
	void SetTournamentOptions();
	
	// Strategy Generation
	void SetIf();
	void SetCharExpression();
	void SetArithExpression();
	void SetAddNewLine();
	void SetGoto();
	void SetMinLines();
	void SetMaxLines();
	void SetGotoJump();

	// Tournament Options
	void ConfigureGangs();
	void ConfigureSpies();
	void ConfigurePrisoners();
	void SetLeaderChange();
	void SetIterations();
	void SetNumGangs();
	void SetNumGangMembers();
	void SetNumberTournaments();
	void SetNumberWinners();
	void SetSentences();

	// Punishment parameters
	void SetCooperate();
	void SetDefect();
	void SetBetrayed();
	void SetTempted();

	// Tournament Helper  functions
	void RunTournament();
	void RunChampionship();
	void RunPrisonerChampionship();
	void RunGangChampionship();
	void RunPrisonerTournament();
	void RunGangTournament();



	const int maxUserOption = 5;		// Maximum integer a user can enter in the menu
	const int minUserOption = 1;		// Minimum integer a user can enter in the menu
	void PrintWelcomeMessage();			// Prints an intro message
	void DisplayOptions();				// Prints list of options user can select on menu screen

	void ResolveInput(int input);		// Act on users menu selection
	void WriteConstantsToFile();		// Saves strategy generation constants to file 


};
