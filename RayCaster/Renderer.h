#pragma once

#include "RayCaster.h"
#include "Game.h"

class Renderer
{
	uint8_t* _sso;
	uint8_t* _tc;
	uint8_t* _tn;
	uint16_t* _tso;
	uint16_t* _tst;

	RayCaster* _rc;
	Game* _g;

public:
	void TraceFrame(Game* g, unsigned char * fb);
	void RenderFrame(Game* g, unsigned char * fb);
	Renderer(RayCaster* rc);
	~Renderer();
};

