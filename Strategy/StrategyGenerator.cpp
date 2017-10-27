#include "StrategyGenerator.h"
#include "../PrisonerStrategyLanguage.h"
#include "../Utility/RandomNumberGenerator.h"
#include "../Utility/FileManager.h"
#include "StrategyConstants.h"
StrategyGenerator::StrategyGenerator(bool safeGeneration, bool gangs) :
m_currentLineNumber(0),
m_highestGotoLine(0),
m_safeGeneration(safeGeneration)
{
	
	StrategyConstants constants = ReadConstants();

	m_charExpressionProb = constants.charExpressionProb;
	m_extendArithmeticProb = constants.extendArithmeticProb; 
	m_addLineProb = constants.addLineProb;			
	m_gotoProb = constants.gotoProb;				
	m_ifProb = constants.ifProb;				

	m_minimumLineNumber = constants.minimumLineNumber;
	if (safeGeneration) {
		m_maximumLineNumber = constants.maximumLineNumber - 1; // Save a line to add an outcome on the end
	}
	else {
		m_maximumLineNumber = constants.maximumLineNumber;
	}

	m_gotoForecast = constants.gotoForecast;

	 // Dictionary of valid variables
	if (gangs) {
		variables = { "ALLOUTCOMES_W", "ALLOUTCOMES_X", "ALLOUTCOMES_Y",
			"ALLOUTCOMES_Z", "ITERATIONS", "MYSCORE",
			"ALLOUTCOMES_A", "ALLOUTCOMES_B", "ALLOUTCOMES_C", };
		charVariables = { "A", "B", "C", "W", "X", "Y", "Z" };
	}
	else {
		charVariables = { "W", "X", "Y", "Z" };
		variables = { "ALLOUTCOMES_W", "ALLOUTCOMES_X", "ALLOUTCOMES_Y", "ALLOUTCOMES_Z", "ITERATIONS", "MYSCORE" };
	}
	if (m_maximumLineNumber && m_maximumLineNumber < m_minimumLineNumber) {
		std::cout << "Error: Trying to generate strategies with max line number smaller than min line number" << std::endl;
	}

}


StrategyGenerator::~StrategyGenerator()
{
}

std::string StrategyGenerator::GenerateExpression(){
	if (RNG->GetRandFloat() < m_charExpressionProb){
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
	} while (RNG->GetRandFloat() < m_extendArithmeticProb);

	buffer += GetRandomRelOp();
	AddSpace(buffer);
	buffer += GetRandomVariable();
	AddSpace(buffer);

	while (RNG->GetRandFloat() < m_extendArithmeticProb){
		buffer += GetRandomArithOp();
		AddSpace(buffer);
		buffer += GetRandomVariable();
		AddSpace(buffer);
	}
	return buffer;
}
std::string StrategyGenerator::GenerateLine(){
	if (RNG->GetRandFloat() < m_ifProb){
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
	//TODO: Refactor
	if (m_safeGeneration) {
		buffer += std::to_string(++m_currentLineNumber);
		AddSpace(buffer);
		buffer += GetRandomOutcome();
		AddEndLine(buffer);
	}
	return buffer;
}

void StrategyGenerator::GenerateStrategy(const std::string& outputFile) {
	FileMgr->WriteFile(outputFile, GenerateStrategy());
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
	if (RNG->GetRandFloat() < m_gotoProb){
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
	int lowerLimit;

	if (m_safeGeneration) {
		lowerLimit = m_currentLineNumber;
	}
	else {
		lowerLimit = 1;
	}

	if (m_maximumLineNumber && m_maximumLineNumber < m_currentLineNumber + m_gotoForecast){
		upperLimit = m_maximumLineNumber;
	}
	else{
		upperLimit = m_currentLineNumber + m_gotoForecast;
	}



	int gotoLine;
	if (m_safeGeneration && (lowerLimit + 1 == upperLimit)) {
		gotoLine = upperLimit;
	}
	else {
		gotoLine = RNG->GetExcludedRandInt(lowerLimit, upperLimit, m_currentLineNumber); //typedef instance
		if (gotoLine > m_highestGotoLine) {
			m_highestGotoLine = gotoLine;
		}
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
		return (RNG->GetRandFloat() < m_addLineProb);
	}
}

void StrategyGenerator::AddSpace(std::string& str){
	str += " ";
}

void StrategyGenerator::AddEndLine(std::string& str){
	str += '\n';
}

std::string StrategyGenerator::GetRandomCharVariable(){
	return charVariables[RNG->GetRandInt(0, charVariables.size())];
}
std::string StrategyGenerator::GetRandomVariable(){ //TODO: What about ints?
	return variables[RNG->GetRandInt(0, variables.size())];
}

std::string StrategyGenerator::GetRandomArithOp(){
	return PSL::arithmeticOps[RNG->GetRandInt(0, PSL::arithmeticOps.size())];
}
std::string StrategyGenerator::GetRandomRelOp(){
	return PSL::relationalOps[RNG->GetRandInt(0, PSL::relationalOps.size())];
}

std::string StrategyGenerator::GetRandomOutcome(){
	return PSL::outcomes[RNG->GetRandInt(0, PSL::outcomes.size())];
}