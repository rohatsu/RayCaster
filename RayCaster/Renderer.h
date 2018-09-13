#pragma once

#include "RayCaster.h"
#include "Game.h"

class Renderer
{
	unsigned char* _wh;
	RayCaster* _rc;
	Game* _g;
public:
	void TraceFrame(Game* g, unsigned char * fb);
	void RenderFrame(Game* g, unsigned char * fb);
	Renderer(RayCaster* rc);
	~Renderer();
};

