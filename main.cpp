#include "Game\Tournament.h"
#include "Utility\RandomNumberGenerator.h"
#include <iostream>

int main()
{
	
	Tournament t(12, "Tournaments//", true, 200, 20);

	t.RunTournament();
	t.CalculateRankings();



}