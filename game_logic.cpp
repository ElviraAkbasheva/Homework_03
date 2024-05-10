#include <iostream>
#include <string>
#include "records_storage.h"
#include "random.h"

int SetUp(std::string highScoresFilename)
{
	std::cout << " > guess_the_number ";
	std::string parameter = "";
	int maxValue = 100;

	//��������� �� ������� �� ������ �������� ���������
	//���� ������ parameter ������, �� ���������� ������������ �������� �� ���������
	getline(std::cin, parameter);
	if (!parameter.length())
	{
		std::cout << std::endl << "You have not entered the parameters" << std::endl
			<< "The default settings will be used" << std::endl;
		return maxValue;
	}
	//��������� �� �������� �� ������ �������� -max
	//���� ��������, �� ��������� ������ �������� ����� � �������� ee maxValue 
	else if (parameter.find("-max ") != std::string::npos)
	{
		std::string s = parameter.erase(0, 5);
		maxValue = atoi(s.c_str());
		return maxValue;
	}
	//��������� �� �������� �� ������ �������� -table
	//���� ��������, �� ��������� ������� ReadFromFile � ReadHighScores, ����� ���� ������� �� ���������
	else if (parameter == "-table")
	{
		ReadFromFile(highScoresFilename);
		ReadHighScores(highScoresFilename);

		std::cout << "\nPress ENTER" << std::endl;
		std::cin.get();

		return 0;
	}
	//��������� �� �������� �� ������ �������� -level
	//���� ��������, �� ��������� ������ �������� ����� � �������� ����� switch ��������������� �������� maxValue 
	else if (parameter.find("-level ") != std::string::npos)
	{
		std::string s = parameter.erase(0, 7);
		switch (atoi(s.c_str()))
		{
		case 1: return 10;  break;
		case 2: return 50;  break;
		case 3: return 100; break;
		default: break;
		}
	}
	else
	{
		std::cout << std::endl << "Invalid parameter" << std::endl
			<< "The default settings will be used" << std::endl;
		return maxValue;
	}
}

void Game(int maxValue, std::string highScoresFilename)
{
	//����������� ��������� �����
	int currentValue = 0;
	int targetValue = GameRandom(maxValue);
	std::cout << std::endl;
	std::cout << "Hello, I'm \"Guess the number\" game:" << std::endl;
	std::cout << "Enter your name, please:" << std::endl;
	std::string userName = "";
	std::cin >> userName;
	std::cout << "Enter your guess (from 0 to " << maxValue << "):" << std::endl;
	int attempts = 0;

	do
	{
		std::cin >> currentValue;
		attempts++;
		if (currentValue < targetValue)
		{
			std::cout << "greater than " << currentValue << std::endl;
		}
		else if (currentValue > targetValue)
		{
			std::cout << "less than " << currentValue << std::endl;
		}
		else
		{
			std::cout << "you win! " << "attempts = " << attempts << std::endl;
			break;
		}
	} while (true);

	WriteToFile(highScoresFilename, userName, attempts);
	ReadHighScores(highScoresFilename);
}