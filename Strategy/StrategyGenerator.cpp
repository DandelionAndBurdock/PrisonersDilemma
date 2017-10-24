#include "StrategyGenerator.h"
#include "../PrisonerStrategyLanguage.h"
#include "../Utility/RandomNumberGenerator.h"
#include "../Utility/FileManager.h"
#include "StrategyConstants.h"
StrategyGenerator::StrategyGenerator() : // TODO: Make a real constructor
m_currentLineNumber(0),
m_highestGotoLine(0)
{
	if (m_maximumLineNumber && m_maximumLineNumber < m_minimumLineNumber) {
		std::cout << "Error: Trying to generate strategies with max line number smaller than min line number" << std::endl;
	}
	rng = RandomNumberGenerator::Instance(); //TODO: Fix this and make the typedef

	StrategyConstants constants = ReadConstants();

	m_charExpressionProb = constants.charExpressionProb;
	m_extendArithmeticProb = constants.extendArithmeticProb; 
	m_addLineProb = constants.addLineProb;			
	m_gotoProb = constants.gotoProb;				
	m_ifProb = constants.ifProb;				

	m_minimumLineNumber = constants.minimumLineNumber;
	m_maximumLineNumber = constants.maximumLineNumber;
	m_gotoForecast = constants.gotoForecast;

}


StrategyGenerator::~StrategyGenerator()
{
}

std::string StrategyGenerator::GenerateExpression(){
	if (rng->GetRandFloat() < m_charExpressionProb){
		return  GenerateCharExpression();
	}
	else{
		return GenerateArithExpression();
	}
}

std::string StrategyGenerator::GenerateCharExpression(){
	std::string buffer = "LASTOUTCOME"; //TODO: Make constant
	AddSpace(buffer);
	buffer += "="; 
	AddSpace(buffer);
	buffer += GetRandomCharVariable();
	return buffer;
}

std::string StrategyGenerator::GenerateArithExpression(){
	std::string buffer = GetRandomVariable();
	AddSpace(buffer);
	do{
		buffer += GetRandomArithOp();
		AddSpace(buffer);
		buffer += GetRandomVariable();
		AddSpace(buffer);
	} while (rng->GetRandFloat() < m_extendArithmeticProb);

	buffer += GetRandomRelOp();
	AddSpace(buffer);
	buffer += GetRandomVariable();
	AddSpace(buffer);

	while (rng->GetRandFloat() < m_extendArithmeticProb){
		buffer += GetRandomArithOp();
		AddSpace(buffer);
		buffer += GetRandomVariable();
		AddSpace(buffer);
	}
	return buffer;
}
std::string StrategyGenerator::GenerateLine(){
	if (rng->GetRandFloat() < m_ifProb){
		return GenerateIfLine();
	}
	else {
		return GetRandomOutcome();
	}
}

std::string StrategyGenerator::GenerateStrategy(){
	m_currentLineNumber = m_highestGotoLine = 0; //TODO: m_
	std::string buffer = std::string(); 
	
	do{
		buffer += std::to_string(++m_currentLineNumber);
		AddSpace(buffer);
		buffer += GenerateLine();
		AddEndLine(buffer);
	} while (ShouldAddAnotherLine());


	return buffer;
}

void StrategyGenerator::GenerateStrategy(const std::string& outputFile) {
	FileManager::Instance()->WriteFile(outputFile, GenerateStrategy());
}

std::string StrategyGenerator::GenerateIfLine(){
	std::string buffer = "IF";
	AddSpace(buffer);
	buffer += GenerateExpression();
	AddSpace(buffer);
	buffer += GenerateAction();
	return buffer;
}

std::string StrategyGenerator::GenerateAction(){
	if (rng->GetRandFloat() < m_gotoProb){
		return GenerateGoto();
	}
	else{
		return GetRandomOutcome();
	}
}

std::string StrategyGenerator::GenerateGoto(){
	std::string buffer = "GOTO";
	AddSpace(buffer);
	int upperLimit;
	if (m_maximumLineNumber && m_maximumLineNumber < m_currentLineNumber + m_gotoForecast){
		upperLimit = m_maximumLineNumber;
	}
	else{
		upperLimit = m_currentLineNumber + m_gotoForecast;
	}

	int gotoLine = RandomNumberGenerator::Instance()->GetExcludedRandInt(1, upperLimit, m_currentLineNumber); //typedef instance
	if (gotoLine > m_highestGotoLine){
		m_highestGotoLine = gotoLine;
	}
	return buffer += std::to_string(gotoLine);
}

bool StrategyGenerator::ShouldAddAnotherLine(){
	if (m_maximumLineNumber && m_currentLineNumber <= m_minimumLineNumber){
		return true;
	}

	if (m_maximumLineNumber && (m_currentLineNumber >= m_maximumLineNumber)){
		return false; 
	}

	if (m_currentLineNumber <= m_highestGotoLine){
		return true;
	}
	else{
		return (rng->GetRandFloat() < m_addLineProb);
	}
}

void StrategyGenerator::AddSpace(std::string& str){
	str += " ";
}

void StrategyGenerator::AddEndLine(std::string& str){
	str += '\n';
}

std::string StrategyGenerator::GetRandomCharVariable(){
	return PSL::charVariables[rng->GetRandInt(0, PSL::charVariables.size())];
}
std::string StrategyGenerator::GetRandomVariable(){ //TODO: What about ints?
	return PSL::variables[rng->GetRandInt(0, PSL::variables.size())];
}

std::string StrategyGenerator::GetRandomArithOp(){
	return PSL::arithmeticOps[rng->GetRandInt(0, PSL::arithmeticOps.size())];
}
std::string StrategyGenerator::GetRandomRelOp(){
	return PSL::relationalOps[rng->GetRandInt(0, PSL::relationalOps.size())];
}

std::string StrategyGenerator::GetRandomOutcome(){
	return PSL::outcomes[rng->GetRandInt(0, PSL::outcomes.size())];
}