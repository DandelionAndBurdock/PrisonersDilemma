#include "StrategyGenerator.h"
#include "../PrisonerStrategyLanguage.h"
#include "../Utility/RandomNumberGenerator.h"
#include "../Utility/FileManager.h"

StrategyGenerator::StrategyGenerator() : // TODO: Make a real constructor
charExpressionProb(0.3),
extendArithmeticProb(0.1),
gotoProb(0.7),
currentLineNumber(0),
gotoForecast(3),
addLineProb(0.8), 
maximumLineNumber(10),
ifProb(0.7),
minimumLineNumber(3),
highestGotoLine(0)
{
	rng = RandomNumberGenerator::Instance();
	//TODO: Check Max Lines greater than min lines
}


StrategyGenerator::~StrategyGenerator()
{
}

std::string StrategyGenerator::GenerateExpression(){
	if (rng->GetRandFloat() < charExpressionProb){
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
	} while (rng->GetRandFloat() < extendArithmeticProb);

	buffer += GetRandomRelOp();
	AddSpace(buffer);
	buffer += GetRandomVariable();
	AddSpace(buffer);

	while (rng->GetRandFloat() < extendArithmeticProb){
		buffer += GetRandomArithOp();
		AddSpace(buffer);
		buffer += GetRandomVariable();
		AddSpace(buffer);
	}
	return buffer;
}
std::string StrategyGenerator::GenerateLine(){
	if (rng->GetRandFloat() < ifProb){
		return GenerateIfLine();
	}
	else {
		return GetRandomOutcome();
	}
}

std::string StrategyGenerator::GenerateStrategy(){
	currentLineNumber = highestGotoLine = 0; //TODO: m_
	std::string buffer = std::string(); 
	
	do{
		buffer += std::to_string(++currentLineNumber);
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
	if (rng->GetRandFloat() < gotoProb){
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
	if (maximumLineNumber < currentLineNumber + gotoForecast){
		upperLimit = maximumLineNumber;
	}
	else{
		upperLimit = currentLineNumber + gotoForecast;
	}

	int gotoLine = RandomNumberGenerator::Instance()->GetExcludedRandInt(1, upperLimit, currentLineNumber); //typedef instance
	if (gotoLine > highestGotoLine){
		highestGotoLine = gotoLine;
	}
	return buffer += std::to_string(gotoLine);
}

bool StrategyGenerator::ShouldAddAnotherLine(){
	if (currentLineNumber <= minimumLineNumber){
		return true;
	}

	if (maximumLineNumber && (currentLineNumber >= maximumLineNumber)){
		return false; 
	}

	if (currentLineNumber <= highestGotoLine){
		return true;
	}
	else{
		return (rng->GetRandFloat() < addLineProb);
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