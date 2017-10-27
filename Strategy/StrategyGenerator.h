// Class: StrategyGenerator
// Description: Randomly generates a strategy in 
// Prisoner Strategy Language 
// Author: Philip Jones
// Date: 17/10/2017
#pragma once

#include <string>
#include <vector>

class StrategyGenerator
{
public:
	StrategyGenerator(bool safeGeneration = false, bool gangs = false);
	~StrategyGenerator();
	// Creates a random stategy and writes it to the outputFile 
	void GenerateStrategy(const std::string& outputFile);

	// Generates a strategy and returns it as a string
	std::string GenerateStrategy();
private:
	// Generate a valid Prisoner Strategy Language expression
	std::string GenerateExpression();
	// Generates a valid expression with character variables
	std::string GenerateCharExpression();
	// Generates a valid arithmetic expresion
	std::string GenerateArithExpression();
	// Generates an IF statement
	std::string GenerateIfLine();
	// Generates an outcome action
	std::string GenerateAction();
	// Generates a GOTO statement
	std::string GenerateGoto();
	// Generates a valid line of code
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

	std::string GetRandomCharVariable(); // Returns a random character variable from the dictionary
	std::string GetRandomVariable();	//  Returns a random variable from the dictionary
	std::string GetRandomArithOp();		// Returns a random arithmetic operator
	std::string GetRandomRelOp();		// Returns a random relational operator
	std::string GetRandomOutcome();		// Returns a random outcome

private:
	 // Appends a space to the end of the string
	void AddSpace(std::string& str);

	// Appends a space to the end of the string
	void AddEndLine(std::string& str);

	// Returns true if the generator should add another line of code
	bool ShouldAddAnotherLine();

	// Dictionaries of variable words
	std::vector<std::string> charVariables;
	std::vector<std::string> variables;
};