#pragma once
#include "RayCaster.h"

class RayCasterFloat :
	public RayCaster
{
protected:
	uint8_t* _map;
	float _px;
	float _py;
	float _pa;
	float* _wd;

	float Distance(float px, float py, float ra);

	bool IsWall(float rx, float ry, float ra);

	float Distance2(float px, float py, float ra);

	void HitLocation(float sx, float sy, float a, float *hx, float *hy, int *dx, int *dy);

	void HitLocation1(float sx, float sy, float a, float *hx, float *hy);

public:
	void Start(uint16_t px, uint16_t py, int16_t pa);

	void Trace(uint16_t x, uint8_t * sso, uint8_t * tso, uint16_t * tst);

	RayCasterFloat(uint8_t *map);
	~RayCasterFloat();
};
