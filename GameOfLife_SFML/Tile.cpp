#include "stdafx.h"
#include "Tile.h"


Tile::Tile(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2) : IEntity(x,y,sprite1,sprite2)
{
	isAlive = false;
}


Tile::~Tile()
{
}

void Tile::SetAliveStatus(bool blockedStatus)
{
	isAlive = blockedStatus;
	if (blockedStatus)
	{
		SetSprite(1);
	}
	else
	{
		SetSprite(0);
	}
}

bool Tile::GetAliveStatus()
{
	return isAlive;
}
