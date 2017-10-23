#include "Game\Tournament.h"
#include "Utility\RandomNumberGenerator.h"
#include <iostream>

int main()
{

	Tournament t(12, "Tournaments//", false, 100, 10);

	t.RunTournament();
	t.CalculateRankings();



}