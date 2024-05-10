#include <iostream>


//Создаём случайное значение
int	GameRandom(int maxValue)
{
	std::srand(std::time(nullptr));
	int randomValue = std::rand() % maxValue;
	return randomValue;
}