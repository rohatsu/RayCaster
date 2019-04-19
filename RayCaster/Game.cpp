#define _USE_MATH_DEFINES

#include "Game.h"
#include "RayCaster.h"

#include <cstdlib>
#include <time.h>

uint8_t* Game::CreateMap()
{
    /*
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
	*/
    return NULL;
}

void Game::Move(int m, int r)
{
    pa += 0.05f * r;
    px += 0.5f * m * sin(pa);
    py += 0.5f * m * cos(pa);

    while(pa < 0)
    {
        pa += 2.0f * M_PI;
    }
    while(pa >= 2.0f * M_PI)
    {
        pa -= 2.0f * M_PI;
    }

    if(px < 1)
    {
        px = 1.01f;
    }
    else if(px > MAP_X - 2)
    {
        px = MAP_X - 2 - 0.01f;
    }
    if(py < 1)
    {
        py = 1.01f;
    }
    else if(py > MAP_Y - 2)
    {
        py = MAP_Y - 2 - 0.01f;
    }
}

Game::Game()
{
    px = 23.03f;
    py = 6.8f;
    pa = 5.25f;
}

Game::~Game() {}
