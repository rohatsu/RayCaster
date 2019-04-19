#define _USE_MATH_DEFINES

#include "Renderer.h"
#include "RayCasterData.h"
#include <math.h>

void Renderer::TraceFrame(Game *g, unsigned char * fb)
{
	_rc->Start(static_cast<uint16_t>(g->px * 256.0f), static_cast<uint16_t>(g->py * 256.0f), static_cast<int16_t>(g->pa / (2.0f * M_PI) * 1024.0f));

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		_rc->Trace(x, _sso + x, _tn + x, _tc + x, _tso + x, _tst + x);
	}
}

void Renderer::RenderFrame(Game *g, unsigned char * fb)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		int sso = static_cast<int>(_sso[x]);
		int ws = (SCREEN_HEIGHT / 2) - sso;
		float to = _tso[x] / 256.0f; // texture offset
		float ts = _tst[x] / 256.0f; // texture step << 8

		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			int i1 = (SCREEN_WIDTH * y) + x;
			if (y < ws || y >(SCREEN_HEIGHT / 2 + sso))
			{
				fb[i1] = 96 + abs(y - SCREEN_HEIGHT / 2);
			}
			else
			{
				// paint texture pixel
				auto ty = (static_cast<int>(round(to)) % 256) >> 2;
				auto tx = static_cast<int>(_tc[x] % 256) >> 2;
				auto tv = _tex[64 * ty + tx];

				to += ts;

				if (_tn[x] == 1 && tv > 0)
				{
					tv >>= 1;
				}
				fb[i1] = tv;// *63 + 0;
			}
		}
	}
}

Renderer::Renderer(RayCaster *rc)
{
	_sso = new uint8_t[SCREEN_WIDTH];
	_tc = new uint8_t[SCREEN_WIDTH];
	_tn = new uint8_t[SCREEN_WIDTH];
	_tso = new uint16_t[SCREEN_WIDTH];
	_tst = new uint16_t[SCREEN_WIDTH];
	_rc = rc;
}

Renderer::~Renderer()
{
}
