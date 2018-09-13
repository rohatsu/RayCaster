#define _USE_MATH_DEFINES

#include "RayCaster.h"
#include <math.h>
#include <stdio.h>

void RayCaster::Start(uint16_t rx, uint16_t ry, int16_t ra)
{
	if (_log)
	{
		printf("=== Start: cell(%d,%d) within=(%d,%d) ra=%d\n", rx / 256, ry / 256, rx % 256, ry % 256, ra);
	}
}

void RayCaster::Step(uint16_t rx, uint16_t ry)
{
	if (_log)
	{
		printf("Step: cell(%d,%d) within=(%d,%d)\n", rx / 256, ry / 256, rx % 256, ry % 256);
	}
}

void RayCaster::Finish(uint16_t rx, uint16_t ry, int16_t dx, int16_t dy)
{
	if (_log)
	{
		printf("Finish: cell(%d,%d) within=(%d,%d), dist=(%d,%d)\n", rx / 256, ry / 256, rx % 256, ry % 256, dx, dy);
	}
}

RayCaster::RayCaster()
{
}

RayCaster::~RayCaster()
{
}
