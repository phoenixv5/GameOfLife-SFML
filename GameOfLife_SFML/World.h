#pragma once
#include "Config.h"
#include "IEntity.h"

class Life;
class SFML_System;
class Tile;
class StartButton;

class World
{
	bool simulationStarted;
	SFML_System* core;
	Life* gol;
	Tile* grid[Config::GRID_WIDTH][Config::GRID_HEIGHT];
	StartButton* button;

	std::vector<Index> CalculateLiveTiles();
	void OnClick();
public:
	World();
	~World();
	void Update();
};

