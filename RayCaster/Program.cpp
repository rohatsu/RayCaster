#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "RayCaster.h"
#include "RayCasterFloat.h"
#include "RayCasterFixed.h"
#include "Renderer.h"
#include "Game.h"

#define TICK_HEIGHT 3
#define TICK_SCALE 32

void DrawBuffer(SDL_Surface* surface, unsigned char *fb, int dx, int dy)
{
	SDL_Rect r;

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			r.x = (x + dx) * SCREEN_SCALE;
			r.y = (y + dy) * SCREEN_SCALE;
			r.w = SCREEN_SCALE;
			r.h = SCREEN_SCALE;
			auto v = fb[(SCREEN_WIDTH * y) + x];
			SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, v, v, v));
		}
	}
}

void DrawTicks(SDL_Surface* surface, Uint32 ticks, int dx, int dy)
{
	SDL_Rect r;

	r.x = dx * SCREEN_SCALE;
	r.y = dy * SCREEN_SCALE;
	r.w = SCREEN_WIDTH * SCREEN_SCALE;
	r.h = TICK_HEIGHT * SCREEN_SCALE;

	SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));

	auto w = ticks * TICK_SCALE * SCREEN_SCALE;

	if (w > SCREEN_WIDTH * SCREEN_SCALE)
	{
		w = 1;
	}

	r.x = dx * SCREEN_SCALE;
	r.y = dy * SCREEN_SCALE;
	r.w = w;
	r.h = TICK_HEIGHT * SCREEN_SCALE;

	SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, 0xFF, 0x00, 0x00));
}

bool ProcessEvent(const SDL_Event& event, int* mDir, int *rDir)
{
	if (event.type == SDL_QUIT)
	{
		return true;
	}
	else if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0)
	{
		auto k = event.key;
		auto p = event.type == SDL_KEYDOWN;
		switch (k.keysym.sym)
		{
		case SDLK_ESCAPE:
			return true;
			break;
		case SDLK_UP:
			if (p)
			{
				*mDir = 1;
			}
			else
			{
				*mDir = 0;
			}
			break;
		case SDLK_DOWN:
			if (p)
			{
				*mDir = -1;
			}
			else
			{
				*mDir = 0;
			}
			break;
		case SDLK_LEFT:
			if (p)
			{
				*rDir = -1;
			}
			else
			{
				*rDir = 0;
			}
			break;
		case SDLK_RIGHT:
			if (p)
			{
				*rDir = 1;
			}
			else
			{
				*rDir = 0;
			}
			break;
		default:
			break;
		}
	}
	return false;
}

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("RayCaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_SCALE * (SCREEN_WIDTH * 2 + 1), SCREEN_SCALE * (SCREEN_HEIGHT + TICK_HEIGHT), SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);

			Game* g = new Game();
			auto map = g->CreateMap();

			RayCaster* rcr = new RayCasterFloat(map);
			Renderer* ri = new Renderer(rcr);
			unsigned char* fbi = new unsigned char[SCREEN_WIDTH * SCREEN_HEIGHT];

			RayCaster* rcf = new RayCasterFixed(map);
			Renderer* rf = new Renderer(rcf);
			unsigned char* fbf = new unsigned char[SCREEN_WIDTH * SCREEN_HEIGHT];

			int mDir = 0, rDir = 0;
			bool q = false;

			SDL_Event event;

			Uint32 ticks;

			while (!q && SDL_WaitEvent(&event))
			{
				ticks = SDL_GetTicks();
				ri->TraceFrame(g, fbi);
				auto iTicks = SDL_GetTicks() - ticks;
				ri->RenderFrame(g, fbi);

				ticks = SDL_GetTicks();
				rf->TraceFrame(g, fbf);
				auto fTicks = SDL_GetTicks() - ticks;
				rf->RenderFrame(g, fbf);

				DrawBuffer(screenSurface, fbi, 0, 0);
				DrawTicks(screenSurface, iTicks, 0, SCREEN_HEIGHT);

				DrawBuffer(screenSurface, fbf, SCREEN_WIDTH + 1, 0);
				DrawTicks(screenSurface, fTicks, SCREEN_WIDTH + 1, SCREEN_HEIGHT);

				SDL_UpdateWindowSurface(window);

				SDL_Delay(1);

				q = ProcessEvent(event, &mDir, &rDir);

				g->Move(mDir, rDir);
			}
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
