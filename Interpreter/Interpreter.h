// Class: Interpreter
// Description: Executes the code of 
// and input strategy string
// Author: Philip Jones
// Date: 17/10/2017

#include <string>
#include <map>
#include <memory>	// For unique_ptr
#include <vector>

#include "Token.h"
#include "../PrisonerStrategyLanguage.h"
#include "Lexer.h"

#pragma once
class Interpreter
{
public:
	// Constructors
	Interpreter(const std::string& fileName, const IntMap& intVars, const CharMap& charVars);
	Interpreter() {}
	Interpreter& operator=(const Interpreter& rhs);
	~Interpreter();

	// Getters
	inline bool IsValid() const { return m_valid; }
	inline std::string GetCode() const { return m_codeString; }

	// Recursively parse the expressions in the statement to get an action
	ActionType GetSelection();
	
	// Setters
	void SetValidStrategy(bool isValid);
private:
	Lexer m_lexer;
	// Load string from file and pass to the lexer for processing into tokens and then expressions
	void LoadCodeFromFile();
	
	// Each Statement in m_code corresponds to one line
	std::vector<std::unique_ptr<Statement>> m_code;

	// Filename of strategy
	std::string m_filename;

	// Code stored in string form
	std::string m_codeString; 

	// Returns iterator of m_code corresponding to line number lineNum
	std::vector<std::unique_ptr<Statement>>::iterator GetIterator(int lineNum);//TODO: Probably should be size_t

	// Maps between Token enums and pointers to the variables
	IntMap intVars; 
	CharMap charVars;

	// True if code compiles correctle and no infinite loops have been detected
	bool m_valid = false;
};

