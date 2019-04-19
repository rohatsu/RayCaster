#pragma once
#include "RayCaster.h"
#include "RayCasterData.h"

class RayCasterFloat : public RayCaster
{
protected:
    float _px;
    float _py;
    float _pa;
    float _hc;
    bool  _hv;

    float Distance(float px, float py, float ra);
    bool  IsWall(float rx, float ry, float ra);
    void  HitLocation(float sx, float sy, float a, float* hx, float* hy, int* dx, int* dy);
    void  HitLocation1(float sx, float sy, float a, float* hx, float* hy);

public:
    void Start(uint16_t playerX, uint16_t playerY, int16_t playerA);
    void Trace(uint16_t screenX, uint8_t* screenY, uint8_t* textureNo, uint8_t* textureX, uint16_t* textureY, uint16_t* textureStep);

    RayCasterFloat();
    ~RayCasterFloat();
};
