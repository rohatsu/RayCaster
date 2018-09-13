#define _USE_MATH_DEFINES

#include "RayCaster.h"
#include "Game.h"

#include <time.h>
#include <cstdlib>

uint8_t* Game::CreateMap()
{
	_map = new uint8_t[MAP_X * MAP_Y];

	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 64; y++)
		{
			if (x == 0 || y == 0 || x == 63 || y == 63)
			{
				_map[MAP_X * y + x] = 1;
			}
			else
			{
				_map[MAP_X * y + x] = 0;
			}
		}
	}

	srand(6);
	
	for (int q = 0; q < 60; q++)
	{
		int x = rand() % 63 + 1;
		int y = rand() % 63 + 1;
		_map[MAP_X * y + x] = 1;
		_map[MAP_X * (MAP_Y - y) + x] = 1;
		_map[MAP_X * (MAP_Y - y) + (MAP_X - x)] = 1;
		_map[MAP_X * y + (MAP_X - x)] = 1;
	}

	return _map;
}

void Game::Move(int m, int r)
{
	pa += 0.05f * r;
	px += 0.5f * m * sin(pa);
	py += 0.5f * m * cos(pa);

	while (pa < 0)
	{
		pa += 2.0f * M_PI;
	}
	while (pa >= 2.0f * M_PI)
	{
		pa -= 2.0f * M_PI;
	}
}

Game::Game()
{
	px = MAP_X / 2+0.5f;
	py = MAP_Y / 2+0.5f;
	pa = 0;
}


Game::~Game()
{
}
