#pragma once

#include <stdint.h>

#ifdef ARDUINO

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 48
#define MAP_X 8
#define MAP_Y 8
#define RAY_STEP 0.05f
#define FOV 1.75f
#define INV_FACTOR 200.0f
#define INV_FACTOR_INT ((uint16_t)(200) * (uint16_t)(256))

#else

#define SCREEN_WIDTH (uint16_t)320
#define SCREEN_HEIGHT (uint16_t)200
#define SCREEN_SCALE 2
#define MAP_X (uint8_t)64
#define MAP_XS (uint8_t)6
#define MAP_Y (uint8_t)64
#define FOV (double)1.75f
#define INV_FACTOR (float)100.0f
#define INV_FACTOR_INT ((uint16_t)(SCREEN_WIDTH * 80))
#define MIN_DIST 256

#endif

class RayCaster
{
protected:
	bool _log = false;

public:
	virtual void Trace(uint16_t px, uint16_t py, int16_t pa, uint8_t * wh) = 0;

	void Start(uint16_t rx, uint16_t ry, int16_t ra);

	void Step(uint16_t rx, uint16_t ry);

	void Finish(uint16_t rx, uint16_t ry, int16_t dx, int16_t dy);

	RayCaster();

	~RayCaster();
};