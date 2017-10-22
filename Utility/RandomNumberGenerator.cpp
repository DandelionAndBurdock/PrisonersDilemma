// Class: Random Number Generator
// Description: Handles the generation of random numbers 
// Author: Philip Jones
// Date: 17/10/2017

#include "RandomNumberGenerator.h"

#include <stdlib.h>		// For srand(), rand()
#include <time.h>		
RandomNumberGenerator::RandomNumberGenerator()
{
	// Initialise random seed
	srand(time(nullptr));
}


RandomNumberGenerator::~RandomNumberGenerator()
{
}


RandomNumberGenerator* RandomNumberGenerator::Instance()
{
	static RandomNumberGenerator instance;
	return &instance;
}


float RandomNumberGenerator::GetRandFloat(float min, float max){
	float random = rand() / float(RAND_MAX);		
	return min + (max - min) * random;
}


int RandomNumberGenerator::GetRandInt(int min, int max){
	return min + (rand() % static_cast<int>(max - min));
}



int RandomNumberGenerator::GetExcludedRandInt(int min, int max, int excluded){
	int randNo = excluded;
	while (randNo == excluded){
		randNo = min + (rand() % static_cast<int>(max - min));
	}
	return randNo;
}

bool RandomNumberGenerator::TrueOrFalse() {
	if (GetRandInt(0, 2) % 2) {
		return true;
	}
	else {
		return false;
	}
}