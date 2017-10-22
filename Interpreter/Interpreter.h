// Class: Interpreter
// Description: Executes the code of 
// and input strategy string
// Author: Philip Jones
// Date: 17/10/2017
//TODO: Make comments look nice
#include <string>
#include <map>
#include <vector>

#include "Token.h"
#include "../PrisonerStrategyLanguage.h"
#include "../Game/PrisonersDilemmaGame.h" //TODO: Including this file just to get enum Slection
#include "Lexer.h"
#include <memory>
#pragma once
class Interpreter
{
public:
	Interpreter(const std::string& fileName, const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars);
	Interpreter() {}
	~Interpreter();
	Interpreter& operator=(const Interpreter& rhs);

	bool IsValid();
	ActionType GetSelection();
private:
	Lexer lexer;

	void LoadCodeFromFile();
	std::vector<std::unique_ptr<Statement>> m_code; // Maps line number to code
	std::string m_filename;

	// Returns iterator of m_code corresponding to line number lineNum
	std::vector<std::unique_ptr<Statement>>::iterator GetIterator(int lineNum);//TODO: Probably should be size_t

	// Debug function
	void PrintToScreen(); 
	const std::map<TokenValue, int*> intVars; 
	const std::map<TokenValue, char*> charVars;

	bool m_valid = false;

};

