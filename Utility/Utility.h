#pragma once

#include <iostream>

// Maths Functions
// Calculates factorial of n (n!)
int factorial(int n);

// Setup Functions
// Creates necessary files and folders
void Setup();

// Creates necessary folders for organisation of tournaments
void SetupDirectories();

// Creates Robot strategy file to chekc for infinite loops
void CreateRobot();

// Creates file for storing strategy generation parameters
void CreateStrategyGenFile();

// Other Useful Functions
// Prints n asertisk characters to the output stream
// If endLine is true also prints a new line
void PrintStarLine(std::ostream& os, bool endLine = false, int n = 40);