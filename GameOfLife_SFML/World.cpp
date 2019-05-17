#include "stdafx.h"
#include "SFML_System.h"
#include "Tile.h"
#include "StartButton.h"
#include "World.h"
#include "Life.h"
#include <iostream>
#include <Windows.h>

World::World()
{
	core = new SFML_System();
	gol - new Life();

	for (int i = 0;i < Config::GRID_WIDTH;i++)
	{
		for (int j = 0;j < Config::GRID_HEIGHT;j++)
		{
			grid[i][j] = new Tile(i, j, core->CreateSprite(Config::TILE_TEXTURE_RECT[0]), core->CreateSprite(Config::TILE_TEXTURE_RECT[1]));
		}
	}

	button = new StartButton(0, Config::GRID_HEIGHT, core->CreateSprite(Config::STARTBUTTON_TEXTURE_RECT[0]), core->CreateSprite(Config::STARTBUTTON_TEXTURE_RECT[1]));
}


World::~World()
{
}

void World::Update()
{
	while (core->WindowStatus())
	{

		sf::Event event;
		while (core->getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				core->getWindow()->close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				OnClick();
			}
		}

		core->RenderClear();

		if (simulationStarted)
		{
			gol->Update();
		}
		for (int i = 0;i < Config::GRID_WIDTH;i++)
		{
			for (int j = 0;j < Config::GRID_HEIGHT;j++)
			{
				if (simulationStarted)
				{
					grid[i][j]->SetAliveStatus(gol->GetStatusAt(Index(i, j)));
				}
				core->DrawEntity(grid[i][j]);
			}
		}
		core->DrawEntity(button);
		core->Display();
		Sleep(100);
	}
}

void World::OnClick()
{
	Index mouseIndex;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		mouseIndex = core->GetMousePosIndex();
	}
	else
	{
		return;
	}

	if (!simulationStarted)
	{
		if (
			core->GetMousePosVector().x >= button->GetSprite().getPosition().x
			&& core->GetMousePosVector().y >= button->GetSprite().getPosition().y
			&& core->GetMousePosVector().x <= button->GetSprite().getPosition().x + button->GetSprite().getGlobalBounds().width
			&& core->GetMousePosVector().y <= button->GetSprite().getPosition().y + button->GetSprite().getGlobalBounds().height
			)
		{
			simulationStarted = true;
			button->SetSprite(1);
			delete gol;
			gol = new Life(CalculateLiveTiles());
			return;
		}


		if (mouseIndex.first < 0 || mouseIndex.second < 0 || mouseIndex.first >= Config::GRID_WIDTH || mouseIndex.second >= Config::GRID_HEIGHT)
		{
			return;
		}

		grid[mouseIndex.first][mouseIndex.second]->SetAliveStatus(!grid[mouseIndex.first][mouseIndex.second]->GetAliveStatus());
	}
}

std::vector<Index> World::CalculateLiveTiles()
{
	std::vector<Index> blockedTiles;

	for (int i = 0;i < Config::GRID_WIDTH;i++)
	{
		for (int j = 0;j < Config::GRID_HEIGHT;j++)
		{
			if (grid[i][j]->GetAliveStatus())
			{
				blockedTiles.push_back(grid[i][j]->GetIndex());
			}
		}
	}

	return blockedTiles;
}