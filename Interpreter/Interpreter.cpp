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

//TODO: Make m_

Interpreter::~Interpreter()
{
}


void Interpreter::LoadCodeFromFile(){
	std::cout << "Loading " << m_filename << "..." << std::endl;
	m_codeString = FileManager::Instance()->ReadFile(m_filename);//TODO: What if file is empty? Will give warning but crash the program
	std::istringstream ss(m_codeString);
	std::string line;
	while (std::getline(ss, line)){
		std::unique_ptr<Statement> linePtr = lexer.Construct(line);
		if (linePtr) {
			m_code.push_back(std::move(linePtr));
		}
		else {
			m_valid = false;
			return;
		}
	}
	m_valid = true;
}

std::vector<std::unique_ptr<Statement>>::iterator Interpreter::GetIterator(int lineNum) {
	return std::find_if(m_code.begin(), m_code.end(), [lineNum](std::unique_ptr<Statement>& s) { return s->m_linenumber == lineNum; });
}


ActionType Interpreter::GetSelection() {
	//TODO: If m_code is empty will crash

	// Need to stack line numbers to check for loops
	//TODO: WHich container is best
	std::vector<int> visitedLines;
	for (auto iter = m_code.begin();;) {
		if (std::find(visitedLines.begin(), visitedLines.end(), (*iter)->m_linenumber) != visitedLines.end()) {
			std::cout << "Logic Error: Inifinite Loop detected in " << m_filename << std::endl; //TODO: Discarding file
			m_valid = false;
			return ActionType::INVALID_ACTION;
		}
		else {
			visitedLines.push_back((*iter)->m_linenumber);
		}
		Action lineAction = (*iter)->Execute(intVars, charVars);
		if (lineAction.m_action == ActionType::GOTO) {
			iter = GetIterator(lineAction.m_line);
		}
		else if (lineAction.m_action == ActionType::NEXT_LINE){
			iter++;
			if (iter == m_code.end()) {
				m_valid = false;
				std::cout << "Logic Error: Program did not return an outcome" << std::endl;
				return ActionType::INVALID_ACTION;
			}
		}
		else {
			return  lineAction.m_action;
		}
	}
}

bool Interpreter::IsValid() {
	return m_valid;
}

Interpreter& Interpreter::operator=(const Interpreter& rhs) {
	
	m_code.clear(); 
	m_codeString = rhs.m_codeString;
	m_filename = rhs.m_filename;
	intVars = rhs.intVars;
	charVars = rhs.charVars;
	lexer.m_lastLineNumber = 0;
	LoadCodeFromFile();
	
	 return *this;
}

std::string Interpreter::GetCode() {
	return m_codeString;
}


void Interpreter::SetValidStrategy(bool isValid) {
	m_valid = isValid;
}
//void Interpreter::PrintToScreen(){
//	for (std::vector<Token>::iterator line = m_code.begin(); line != m_code.end(); ++line){
//		for (auto& token : *line){
//			std::cout << token << " ";
//		}
//		std::cout << std::endl;
//	}
//}

