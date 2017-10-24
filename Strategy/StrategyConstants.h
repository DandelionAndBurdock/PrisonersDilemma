#pragma once

//TODO: Make a namespace
#include <string>

const std::string strategyFile = "StrategyGenerationConstants.txt";

const int NUM_FLOAT_VARIABLES = 5;
const int NUM_INT_VARIABLES = 3;

const std::string floatVariables[NUM_FLOAT_VARIABLES] = { "CharacterExpressionProbability", "ExtendArithmeticExpressionProbability",
"GotoProbability", "IfProbability", "AddLineProbability" };

const std::string intVariables[NUM_INT_VARIABLES] = { "GotoForecast", "MaximumLineNumber ",
"MinimumLineNumber "};

struct StrategyConstants {
	float charExpressionProb;	// Probability to generate a character variable expression
	float extendArithmeticProb; // Probability to extend an arithmetic expression
	float addLineProb;			// Probability to keep adding more lines
	float gotoProb;				// Probability of a goto statement to appear at the end of an If
	float ifProb;				// Probability of a goto statement to appear at the end of an If

	int minimumLineNumber;		// Minimum number of lines that must be generated. Note this can be altered by line numbert
	int maximumLineNumber;		// Negative if user does not set it	
	int gotoForecast;			// 
};

StrategyConstants ReadConstants();