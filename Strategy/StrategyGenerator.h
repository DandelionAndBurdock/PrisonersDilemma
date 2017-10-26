// Class: StrategyGenerator
// Description: Randomly generates a strategy in 
// Prisoner Strategy Language 
// Author: Philip Jones
// Date: 17/10/2017
#pragma once

#include <string>
#include <vector>

class RandomNumberGenerator;


class StrategyGenerator
{
public:
	StrategyGenerator(bool safeGeneration = false, bool gangs = false);
	~StrategyGenerator();
	void GenerateStrategy(const std::string& outputFile);
	std::string GenerateStrategy();
public: //TODO: private
	// Generate a valid Prisoner Strategy Language expression
	std::string GenerateExpression();
	std::string GenerateCharExpression();
	std::string GenerateArithExpression();
	std::string GenerateIfLine();
	std::string GenerateAction();
	std::string GenerateGoto();
	std::string GenerateLine();
private:
	float m_charExpressionProb;	// Probability to generate a character variable expression
	float m_extendArithmeticProb; // Probability to extend an arithmetic expression
	float m_addLineProb;			// Probability to keep adding more lines
	float m_gotoProb;				// Probability of a goto statement to appear at the end of an If
	float m_ifProb;				// Probability of a goto statement to appear at the end of an If

	int m_currentLineNumber;
	int m_minimumLineNumber;		// Minimum number of lines that must be generated. Note this can be altered by line numbert
	int m_maximumLineNumber;		// Negative if user does not set it	
	int m_gotoForecast;			// 
	int m_highestGotoLine;		// Highest line number which there is a goto to

	bool m_safeGeneration;			// If safe generation is true goto will not jump backwards and an outcome will be appended on the end

	std::string GetRandomCharVariable();
	std::string GetRandomVariable();
	std::string GetRandomArithOp();
	std::string GetRandomRelOp();
	std::string GetRandomOutcome();

	RandomNumberGenerator* rng;//TODO: Remove this
private:
	 // Appends a space to the end of the string
	void AddSpace(std::string& str);

	// Appends a space to the end of the string
	void AddEndLine(std::string& str);

	bool ShouldAddAnotherLine();

	std::vector<std::string> charVariables;
	std::vector<std::string> variables;
};

// Strategy Class: Contains number of lines
//TODO: Const