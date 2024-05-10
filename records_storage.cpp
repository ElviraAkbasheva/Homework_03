#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Записываем в файл
void WriteToFile(std::string fileName, std::string userName, int attempts)
{
	std::ofstream saveToFile{ fileName, std::ios::app };

	if (!saveToFile.is_open())
	{
		std::cout << "Failed to open file for write: " << fileName << "!" << std::endl;
		return;
	}

	saveToFile << userName << '\t';
	saveToFile << attempts;
	saveToFile << std::endl;
}

//Читаем из файла результаты в вектор
std::vector<std::string> Read(std::string fileName)
{
	std::ifstream readFromFile{ fileName };
	std::vector<std::string> scoreTable;

	if (!readFromFile.is_open())
	{
		std::cout << "Failed to open file for read: " << fileName << "!" << std::endl;
		return scoreTable;
	}

	while (true)
	{
		std::string gameResult;
		readFromFile >> gameResult;
		scoreTable.push_back(gameResult);

		if (readFromFile.fail())
		{
			break;
		}
	}
	return scoreTable;
}

// Печатаем в консоль из вектора
void Print(std::vector<std::string> gameResult)
{
	for (int i = 0; i < gameResult.size() - 1; i += 2)
	{
		if (gameResult[i] != "")
		{
			std::cout << gameResult[i];
			std::cout << "\t" << gameResult[i + 1] << "\n";
		}
		else
		{
			return;
		}
	}
}

//Читаем из файла, печатаем в консоль
void ReadFromFile(std::string fileName)
{
	Print(Read(fileName));
}

//Чтение из файла лучших результатов и печать в консоль
void ReadHighScores(std::string fileName)
{
	std::cout << std::endl << "High scores table:" << std::endl;

	std::vector<std::string> scoreTable = Read(fileName);
	int size = scoreTable.size();

	std::vector<std::string> uniqumUsers(size);
	//std::vector<std::string> uniqumUsers;

	//Заполняем массив только уникальными пользователями
	int k = 0; //Позиция уникального пользователя
	for (int i = 0; i < size - 1; i += 2)
	{
		int check_1 = 0;
		int check_2 = 0;

		for (int j = 0;j < size - 1;j += 2)
		{
			if (scoreTable[i] != uniqumUsers[j])
			{
				check_1++;
			}
			if (scoreTable[i] == uniqumUsers[j])
			{
				check_2++;
			}
		}

		if (check_1 > 0 && check_2 == 0)
		{
			uniqumUsers[k] = scoreTable[i];
			k += 2;
		}
	}

	//Нахождение наилучших результатов каждого пользователя
	for (int i = 0; i < size - 1; i += 2)
	{
		if (uniqumUsers[i] != "")
		{
			std::string user = uniqumUsers[i];
			std::string score = std::to_string(INT_MAX);

			for (int j = 0; j < size - 1;j += 2)
			{
				if (scoreTable[j] == user && atoi(scoreTable[j + 1].c_str()) < atoi(score.c_str()))
				{
					score = scoreTable[j + 1];
				}
			}
			uniqumUsers[i + 1] = score;
		}
		else
		{
			break;
		}
	}

	// Печатаем в консоль
	Print(uniqumUsers);
}