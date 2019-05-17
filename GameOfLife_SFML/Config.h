#pragma once
#include <SFML/Graphics.hpp>

class Config
{
public:
	const static sf::IntRect TILE_TEXTURE_RECT[2];
	const static sf::IntRect STARTBUTTON_TEXTURE_RECT[2];

	const static float TILE_SCALE;

	const static int GRID_WIDTH = 80;
	const static int GRID_HEIGHT = 50;
	const static int SCREEN_WIDTH = 1280;
	const static int SCREEN_HEIGHT = 720;
	const static int TILE_SIZE = 128;

	const static int INITIAL = 500;
};
