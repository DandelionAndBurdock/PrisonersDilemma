#pragma once
class GameManager
{
public:
	GameManager();
	void Run();
	~GameManager();

private:
	const int maxUserOption = 6;
	const int minUserOption = 1;
	void PrintWelcomeMessage();
	void DisplayOptions();

	int GetUserInput();
};

