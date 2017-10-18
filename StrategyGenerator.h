// Class: StrategyGenerator
// Description: Randomly generates a strategy in 
// Prisoner Strategy Language 
// Author: Philip Jones
// Date: 17/10/2017
#pragma once

#include <string>

#include "RandomNumberGenerator.h"


class StrategyGenerator
{
public:
	StrategyGenerator();
	~StrategyGenerator();

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
	float charExpressionProb;	// Probability to generate a character variable expression
	float extendArithmeticProb; // Probability to extend an arithmetic expression
	float addLineProb;			// Probability to keep adding more lines
	float gotoProb;				// Probability of a goto statement to appear at the end of an If
	float ifProb;				// Probability of a goto statement to appear at the end of an If

	int currentLineNumber;
	int minimumLineNumber;		// Minimum number of lines that must be generated. Note this can be altered by line numbert
	int maximumLineNumber;		// Negative if user does not set it	
	int gotoForecast;			// 
	int highestGotoLine;		// Highest line number which there is a goto to



	std::string GetRandomCharVariable();
	std::string GetRandomVariable();
	std::string GetRandomArithOp();
	std::string GetRandomRelOp();
	std::string GetRandomOutcome();
	RandomNumberGenerator rng;


private:
	 // Appends a space to the end of the string
	void AddSpace(std::string& str);

	// Appends a space to the end of the string
	void AddEndLine(std::string& str);

	bool ShouldAddAnotherLine();
};

// Strategy Class: Contains number of lines
//TODO: Const