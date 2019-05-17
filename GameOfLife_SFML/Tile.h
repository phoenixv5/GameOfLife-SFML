#pragma once
#include "IEntity.h"

class Tile :
	public IEntity
{
	bool isAlive;
public:
	Tile(int x, int y, sf::Sprite sprite1, sf::Sprite sprite2);
	~Tile();
	void SetAliveStatus(bool status);
	bool GetAliveStatus();
};

