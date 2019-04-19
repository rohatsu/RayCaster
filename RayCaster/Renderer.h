#pragma once

#include "Game.h"
#include "RayCaster.h"

class Renderer
{
    RayCaster* _rc;
    Game*      _g;

public:
    void TraceFrame(Game* g, unsigned char* frameBuffer);
    Renderer(RayCaster* rc);
    ~Renderer();
};
