#include <iostream>
#include <string>
#include "records_storage.h"
#include "random.h"
#include "game_logic.h"

int main()
{
	const std::string highScoresFilename = "high_scores.txt";

	int maxValue= SetUp(highScoresFilename);
	if (maxValue == 0)
		return 0;

	Game(maxValue, highScoresFilename);

	std::cin.ignore();
	std::cout << "\nPress ENTER" << std::endl;
	std::cin.get();
}
