#define _USE_MATH_DEFINES

#include "Renderer.h"
#include <math.h>

void Renderer::TraceFrame(Game *g, unsigned char * fb)
{
	_rc->Start(static_cast<uint16_t>(g->px * 256.0f), static_cast<uint16_t>(g->py * 256.0f), static_cast<int16_t>(g->pa / (2.0f * M_PI) * 1024.0f));

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		uint16_t tst;
		uint8_t sso;
		uint8_t tso;

		_rc->Trace(x, &sso, &tso, &tst);
		_wh[x] = sso;
	}
}

void Renderer::RenderFrame(Game *g, unsigned char * fb)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		int ws = (SCREEN_HEIGHT / 2) - static_cast<int>(_wh[x]);

		for (int y = 0; y < SCREEN_HEIGHT / 2; y++)
		{
			int i1 = (SCREEN_WIDTH * y) + x;
			int i2 = (SCREEN_WIDTH * (SCREEN_HEIGHT - y - 1)) + x;
			if (y < ws)
			{
				fb[i1] = 0;
				fb[i2] = 0;
			}
			else
			{
				fb[i1] = 1;
				fb[i2] = 1;
			}
		}
	}
}

Renderer::Renderer(RayCaster *rc)
{
	_wh = new unsigned char[SCREEN_WIDTH];
	_rc = rc;
}

Renderer::~Renderer()
{
}
