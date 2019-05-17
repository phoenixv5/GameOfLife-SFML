#pragma once
#include "Config.h"
#include "IEntity.h"

enum Status
{
	Status_M1,
	Status_M2
};

class Life
{
	Status currentStatus;
	bool m1[Config::GRID_WIDTH][Config::GRID_HEIGHT];
	bool m2[Config::GRID_WIDTH][Config::GRID_HEIGHT];
	const char live = '*';
	const char dead = ' ';
	int FindNeighbors(Status m, int x, int y);
	void CoreLoop(); // For console display. Currently disabled!
public:
	void Update();
	void PrintCurrent();
	bool GetStatusAt(Index index);
	Life();
	Life(std::vector<Index> live);
};

