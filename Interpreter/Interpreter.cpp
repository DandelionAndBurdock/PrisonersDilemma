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

Interpreter::Interpreter(const std::string& fileName, const std::map<TokenValue, int*>& intVars, const std::map<TokenValue, char*>& charVars) :
m_filename(fileName), intVars(intVars), charVars(charVars)
{
	LoadCodeFromFile();
}

//TODO: Make m_

Interpreter::~Interpreter()
{
}


void Interpreter::LoadCodeFromFile(){
	std::cout << "Loading " << m_filename << "..." << std::endl;
	std::string source = FileManager::Instance()->ReadFile(m_filename);
	std::istringstream ss(source);
	std::string line;
	while (std::getline(ss, line)){
		m_code.push_back(lexer.Construct(line)); //TODO: Should check if returned invalid token
	}
	int lineNumber;
}

std::vector<std::unique_ptr<Statement>>::iterator Interpreter::GetIterator(int lineNum) {
	return std::find_if(m_code.begin(), m_code.end(), [lineNum](std::unique_ptr<Statement>& s) { return s->m_linenumber == lineNum; });
}


ActionType Interpreter::GetSelection() {
	// Need to stack line numbers to check for loops
	//TODO: WHich container is best
	std::vector<int> visitedLines;
	for (auto iter = m_code.begin();;) {
		if (std::find(visitedLines.begin(), visitedLines.end(), (*iter)->m_linenumber) != visitedLines.end()) {
			std::cout << "Logic Error: Inifinite Loop detected" << std::endl;
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
		}
		else {
			return  lineAction.m_action;
		}
	}
}


//void Interpreter::PrintToScreen(){
//	for (std::vector<Token>::iterator line = m_code.begin(); line != m_code.end(); ++line){
//		for (auto& token : *line){
//			std::cout << token << " ";
//		}
//		std::cout << std::endl;
//	}
//}

