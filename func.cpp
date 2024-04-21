#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include<climits>
#include "guess_header.h"

//������ ��������� ��������
int	GameRandom(int maxValue)
{
	std::srand(std::time(nullptr));
	int randomValue = std::rand() % maxValue;
	return randomValue;
}

//���������� � ����
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

//������ �� �����
void ReadFromFile(std::string fileName)
{
	std::ifstream readFromFile{ fileName };
	if (!readFromFile.is_open())
	{
		std::cout << "Failed to open file for read: " << fileName << "!" << std::endl;
		return;
	}

	std::cout << std::endl << "Scores table:" << std::endl;

	std::string userName;
	int highScore = 0;
	while (true)
	{
		readFromFile >> userName;
		readFromFile >> highScore;

		if (readFromFile.fail())
		{
			break;
		}

		std::cout << userName << '\t' << highScore << std::endl;
	}
}

//������ �� ����� ������ ����������� 
void ReadHighScores(std::string fileName)
{
	std::ifstream readFromFile_1{ fileName };
	if (!readFromFile_1.is_open())
	{
		std::cout << "Failed to open file for read: " << fileName << "!" << std::endl;
		return;
	}

	std::cout << std::endl << "High scores table:" << std::endl;

//������� ���������� ����� � �����
	int counter = 0;
	while (true)
	{
		std::string s;
		getline(readFromFile_1, s);
		if (!readFromFile_1.eof())
		{
			counter++;
		}
		else
		{
			break;
		}
	}

	std::ifstream readFromFile_2{ fileName };

	//�������� ������������ ������ ��� ��������� ������
	std::string** array = new std::string * [counter]; //������ ����������
	for (int i = 0; i < counter; i++)
	{
		array[i] = new std::string[2];
	}
	//��������� ��������� ������������ ������ ������� �� ������
	for (int i = 0; i < counter; i++)
	{
		readFromFile_2 >> array[i][0];
		readFromFile_2 >> array[i][1];
	}
	//�������� ������������ ������ ��� ���������� ������ ���������� �������������
	std::string* uniqumUsers = new std::string[counter];
	//��������� ������ ������ ����������� ��������������
	int k = 0; //������� ����������� ������������
	for (int i = 0; i < counter;i++)
	{
		int check_1 = 0;
		int check_2 = 0;

		for (int j = 0;j < counter;j++)
		{
			if (array[i][0] != uniqumUsers[j])
			{
				check_1++;
			}
			if (array[i][0] == uniqumUsers[j])
			{
				check_2++;
			}
		}

		if (check_1 > 0 && check_2 == 0)
		{
			uniqumUsers[k] = array[i][0];
			k++;
		}
	}
    //���������� � ����� � ������� ��������� ����������� ������� ������������
	for (int i = 0;i < counter;i++)
	{
		if (uniqumUsers[i] != "")
		{
			std::string user = uniqumUsers[i];
			std::string score = std::to_string(INT_MAX);

			for (int j = 0; j < counter;j++)
			{
				if (array[j][0] == user && atoi(array[j][1].c_str()) < atoi(score.c_str()))
				{
					score = array[j][1];
				}
			}
			std::cout << user << "\t" << score << std::endl;
		}
		else
		{
			break;
		}
	}
	//������� ������������ ������
	for (int i = 0;i < counter;i++)
	{
		delete[] array[i];
	}
	delete[] array;

	delete[] uniqumUsers;
}