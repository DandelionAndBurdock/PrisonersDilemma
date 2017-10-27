#include "Interpreter.h"

// Make sure line numbers aren't repeated
// Strip line numbers 
// Checck has a valid solution
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm> // find_if()
#include <set>

#include "../Utility/FileManager.h"
#include "Lexer.h"

Interpreter::Interpreter(const std::string& fileName, const IntMap& intVars, const CharMap& charVars) :
m_filename(fileName), intVars(intVars), charVars(charVars), m_codeString(std::string())
{
	LoadCodeFromFile();
}



Interpreter::~Interpreter()
{
}


void Interpreter::LoadCodeFromFile(){
	m_codeString = FileMgr->ReadFile(m_filename);
	std::istringstream ss(m_codeString);
	std::string line;
	while (std::getline(ss, line)){
		if (line.size()) {
			std::unique_ptr<Statement> linePtr = m_lexer.Construct(line);
		
		if (linePtr) {
			m_code.push_back(std::move(linePtr));
		}
		else {
			m_valid = false;
			return;
		}
		}
	}
	m_valid = true;
}

std::vector<std::unique_ptr<Statement>>::iterator Interpreter::GetIterator(int lineNum) {
	return std::find_if(m_code.begin(), m_code.end(), [lineNum](std::unique_ptr<Statement>& s) { return s->m_linenumber == lineNum; });
}


ActionType Interpreter::GetSelection() {
	if (m_code.empty()) {
		std::cout << "Error: Trying to interpret empty code" << std::endl;
		return ActionType::INVALID_ACTION;
	}

	// Keep track of visited lines. If a line is visited twice code is stuck in an infinite loop
	std::vector<int> visitedLines; 
	for (auto iter = m_code.begin();;) {
		if (std::find(visitedLines.begin(), visitedLines.end(), (*iter)->m_linenumber) != visitedLines.end()) {
			std::cout << "Logic Error: Infinite Loop detected in " << m_filename << std::endl; 
			m_valid = false;
			return ActionType::INVALID_ACTION;
		}
		else {
			visitedLines.push_back((*iter)->m_linenumber);
		}
		// Evaluate this line
		Action lineAction = (*iter)->Execute(intVars, charVars);
		if (lineAction.m_action == ActionType::GOTO) {
			iter = GetIterator(lineAction.m_line);
		}
		else if (lineAction.m_action == ActionType::NEXT_LINE){ // If the IF statement evaluates to false move to the next line
			iter++;
			if (iter == m_code.end()) {
				m_valid = false;
				std::cout << "Logic Error: Program did not return an outcome" << std::endl;
				return ActionType::INVALID_ACTION;
			}
		}
		else { // If not GOTO or NEXT_LINE have found an outcome action
			return  lineAction.m_action;
		}
	}
}


Interpreter& Interpreter::operator=(const Interpreter& rhs) {
	m_code.clear(); 
	m_codeString = rhs.m_codeString;
	m_filename = rhs.m_filename;
	intVars = rhs.intVars;
	charVars = rhs.charVars;
	m_lexer.m_lastLineNumber = 0;
	LoadCodeFromFile();
	
	 return *this;
}

void Interpreter::SetValidStrategy(bool isValid) {
	m_valid = isValid;
}