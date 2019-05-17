#include "stdafx.h"
#include "Life.h"
#include <iostream>
#include <time.h>
#include <Windows.h>

void Life::PrintCurrent()
{
	COORD c = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

	if (currentStatus == Status::Status_M1)
	{
		for (int j = 0;j < Config::GRID_HEIGHT;j++)
		{
			for (int i = 0;i < Config::GRID_WIDTH;i++)
			{
				if (m1[i][j])
				{
					std::cout << live;
				}
				else
				{
					std::cout << dead;
				}
			}

			std::cout << std::endl;
		}
	}
	else if (currentStatus == Status::Status_M2)
	{
		for (int j = 0;j < Config::GRID_HEIGHT;j++)
		{
			for (int i = 0;i < Config::GRID_WIDTH;i++)
			{
				if (m2[i][j])
				{
					std::cout << live;
				}
				else
				{
					std::cout << dead;
				}
			}

			std::cout << std::endl;
		}
	}
}

bool Life::GetStatusAt(Index index)
{
	if (index.first < 0 || index.first >= Config::GRID_WIDTH || index.second < 0 || index.second > Config::GRID_HEIGHT)
	{
		return false;
	}

	if (currentStatus == Status::Status_M1)
	{
		return m1[index.first][index.second];
	}
	else if (currentStatus == Status::Status_M2)
	{
		return m2[index.first][index.second];
	}
	return false;
}

void Life::CoreLoop()
{
	while (true)
	{
		PrintCurrent();
		Update();
		Sleep(16);
	}
}

int Life::FindNeighbors(Status m, int x, int y)
{
	int neighbors = 0;
	if (m == Status_M1)
	{
		for (int i = x - 1; i <= x + 1;i++)
		{
			for (int j = y - 1; j <= y + 1;j++)
			{
				if (i < 0 || i >= Config::GRID_WIDTH || j < 0 || j > Config::GRID_HEIGHT)
				{
					continue;
				}
				else if (i == x && j == y)
				{
					continue;
				}
				else
				{
					if (m1[i][j])
					{
						neighbors++;
					}
				}
			}
		}
	}
	else if (m == Status_M2)
	{
		for (int i = x - 1; i <= x + 1;i++)
		{
			for (int j = y - 1; j <= y + 1;j++)
			{
				if (i < 0 || i >= Config::GRID_WIDTH || j < 0 || j > Config::GRID_HEIGHT)
				{
					continue;
				}
				else if (i == x && j == y)
				{
					continue;
				}
				else
				{
					if (m2[i][j])
					{
						neighbors++;
					}
				}
			}
		}
	}

	return neighbors;
}

void Life::Update()
{
	if (currentStatus == Status::Status_M1)
	{
		for (int i = 0;i < Config::GRID_WIDTH;i++)
		{
			for (int j = 0;j < Config::GRID_HEIGHT;j++)
			{
				int temp = FindNeighbors(Status::Status_M1, i, j);
				switch (temp)
				{
				case 0:m2[i][j] = false; break;
				case 1:m2[i][j] = false; break;
				case 2:m2[i][j] = m1[i][j]; break;
				case 3:m2[i][j] = true; break;
				case 4:m2[i][j] = false; break;
				case 5:m2[i][j] = false; break;
				case 6:m2[i][j] = false; break;
				case 7:m2[i][j] = false; break;
				case 8:m2[i][j] = false; break;
				default:break;
				}
			}
		}
		currentStatus = Status_M2;
	}
	else if (currentStatus == Status::Status_M2)
	{
		for (int i = 0;i < Config::GRID_WIDTH;i++)
		{
			for (int j = 0;j < Config::GRID_HEIGHT;j++)
			{
				int temp = FindNeighbors(Status::Status_M2, i, j);
				switch (temp)
				{
				case 0:m1[i][j] = false; break;
				case 1:m1[i][j] = false; break;
				case 2:m1[i][j] = m2[i][j]; break;
				case 3:m1[i][j] = true; break;
				case 4:m1[i][j] = false; break;
				case 5:m1[i][j] = false; break;
				case 6:m1[i][j] = false; break;
				case 7:m1[i][j] = false; break;
				case 8:m1[i][j] = false; break;
				default:break;
				}
			}
		}
		currentStatus = Status_M1;
	}
}

Life::Life()
{
	srand(time(NULL));

	for (int i = 0;i < Config::GRID_WIDTH;i++)
	{
		for (int j = 0;j < Config::GRID_HEIGHT;j++)
		{
			m1[i][j] = m2[i][j] = false;
		}
	}

	for (int i = 0;i < Config::INITIAL;i++)
	{
		int t1 = rand() % Config::GRID_WIDTH;
		int t2 = rand() % Config::GRID_HEIGHT;

		if (t1 < 0 || t1 >= Config::GRID_WIDTH || t2 < 0 || t2 > Config::GRID_HEIGHT)
		{
			continue;
		}
		else
		{
			m1[t1][t2] = true;
		}
	}

	currentStatus = Status::Status_M1;
}

Life::Life(std::vector<Index> live)
{
	for (int i = 0;i < Config::GRID_WIDTH;i++)
	{
		for (int j = 0;j < Config::GRID_HEIGHT;j++)
		{
			m1[i][j] = m2[i][j] = false;
		}
	}

	for (auto it : live)
	{
		if (it.first < 0 || it.first >= Config::GRID_WIDTH || it.second < 0 || it.second > Config::GRID_HEIGHT)
		{
			continue;
		}
		else
		{
			m1[it.first][it.second] = m2[it.first][it.second] = true;
		}
	}

	currentStatus = Status::Status_M1;
}
