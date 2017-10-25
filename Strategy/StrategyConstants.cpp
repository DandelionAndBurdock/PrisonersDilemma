#include "StrategyConstants.h"

#include <sstream>

#include "../Utility/FileManager.h"
StrategyConstants ReadConstants() {
	std::string file = FileManager::Instance()->ReadFile(strategyFile);

	std::istringstream ss(file);
	std::string name;
	float floats[NUM_FLOAT_VARIABLES];
	float ints[NUM_INT_VARIABLES];
	// Read in float variables
	for (int i = 0; i < NUM_FLOAT_VARIABLES; ++i) {
		ss >> name >> floats[i]; //TODO: Checking
	}
	// Read in int variables
	for (int i = 0; i < NUM_INT_VARIABLES; ++i) {
		ss >> name >> ints[i]; //TODO: Checking
	}

	StrategyConstants constants;
	constants.charExpressionProb = floats[0];
	constants.extendArithmeticProb = floats[1];
	constants.gotoProb = floats[2];
	constants.ifProb = floats[3];
	constants.addLineProb = floats[4];
	
	constants.gotoForecast = ints[0];
	constants.maximumLineNumber = ints[1];
	constants.minimumLineNumber = ints[2];

	return constants; //TODO: Possibly more efficient to return on the heap
}

void WriteConstants(StrategyConstants& constants) {

	std::string s = floatVariables[0];
	s += ' ';
	s += std::to_string(constants.charExpressionProb);
	s += '\n';

	s += floatVariables[1];
	s += ' ';
	s += std::to_string(constants.extendArithmeticProb);
	s += '\n';

	s += floatVariables[2];
	s += ' ';
	s += std::to_string(constants.gotoProb);
	s += '\n';

	s += floatVariables[3];
	s += ' ';
	s += std::to_string(constants.ifProb);
	s += '\n';

	s += floatVariables[4];
	s += ' ';
	s += std::to_string(constants.addLineProb);
	s += '\n';

	s += intVariables[0];
	s += ' ';
	s += std::to_string(constants.gotoForecast);
	s += '\n';

	s += intVariables[1];
	s += ' ';
	s += std::to_string(constants.maximumLineNumber);
	s += '\n';

	s += intVariables[2];
	s += ' ';
	s += std::to_string(constants.minimumLineNumber);
	s += '\n';

	std::cout << s;
	FileManager::Instance()->WriteFile(strategyFile, s);

	return;
}