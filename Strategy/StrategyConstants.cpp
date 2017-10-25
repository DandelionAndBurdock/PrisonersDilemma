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


	return; //TODO: Possibly more efficient to return on the heap
}