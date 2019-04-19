// floating-point implementation for testing/comparison

#define _USE_MATH_DEFINES

#include "RayCasterFloat.h"
#include <math.h>

bool RayCasterFloat::IsWall(float rx, float ry, float ra)
{
    float x  = 0;
    float y  = 0;
    float sx = modff(rx, &x);
    float sy = modff(ry, &y);

    int ibx = static_cast<int>(x);
    int iby = static_cast<int>(y);

    if(ibx < 0 || iby < 0 || ibx >= MAP_X - 1 || iby >= MAP_Y - 1)
    {
        return true;
    }
    return g_map[+(ibx >> 3) + (iby << (MAP_XS - 3))] & (1 << (8 - (ibx & 0x7)));
}

float RayCasterFloat::Distance(float px, float py, float ra)
{
    float rx, ry;

    rx = px;
    ry = py;

    while(ra < 0)
    {
        ra += 2.0f * M_PI;
    }
    while(ra >= 2.0f * M_PI)
    {
        ra -= 2.0f * M_PI;
    }

    // xStep/yStep=tan(a)

    int tileStepX = 1;
    int tileStepY = 1;
    if(ra > M_PI)
    {
        tileStepX = -1;
    }
    if(ra > M_PI_2 && ra < 3 * M_PI_2)
    {
        tileStepY = -1;
    }

    //float yIntercept = ry + yStep; // next intercept with vertical line
    //float xIntercept = rx + xStep; // next intercept with horizontal line

    float x  = 0;
    float y  = 0;
    float sx = modff(rx, &x);
    float sy = modff(ry, &y);

    float sdx, sdy;
    if(ra <= M_PI_2)
    {
        sdx = (1 - sy) * tan(ra);
        sdy = (1 - sx) / tan(ra);
    }
    else if(ra <= M_PI)
    {
        if(sy == 0)
        {
            sdx = (1) * fabs(tan(ra));
        }
        else
        {
            sdx = (sy)*fabs(tan(ra));
        }
        sdy = -(1 - sx) / fabs(tan(ra));
    }
    else if(ra < 3 * M_PI_2)
    {
        if(sy == 0)
        {
            sdx = -(1) * fabs(tan(ra));
        }
        else
        {
            sdx = -(sy)*fabs(tan(ra));
        }
        if(sx == 0)
        {
            sdy = -(1) / fabs(tan(ra));
        }
        else
        {
            sdy = -(sx) / fabs(tan(ra));
        }
    }
    else
    {
        sdx = -(1 - sy) * fabs(tan(ra));
        if(sx == 0)
        {
            sdy = (1) / fabs(tan(ra));
        }
        else
        {
            sdy = (sx) / fabs(tan(ra));
        }
    }

    float xIntercept    = rx + sdx;
    float yIntercept    = ry + sdy;
    float xStep         = fabs(tan(ra)) * tileStepX;
    float yStep         = fabs(1 / tan(ra)) * tileStepY;
    bool  hitVert       = false;
    bool  hitHoriz      = false;
    bool  somethingDone = false;
    int   isTop         = 0;
    int   isRight       = 0;

    do
    {
        somethingDone = false;
        while(((tileStepY == 1 && (yIntercept <= y + 1)) || (tileStepY == -1 && (yIntercept >= y))))
        {
            somethingDone = true;
            x += tileStepX;
            if(IsWall(x, yIntercept, ra))
            {
                hitVert       = true;
                rx            = x + (tileStepX == -1 ? 1 : 0);
                ry            = yIntercept;
                _hitOffset    = yIntercept;
                _hitDirection = true;
                break;
            }
            yIntercept += yStep;
        }
        while(!hitVert && ((tileStepX == 1 && (xIntercept <= x + 1)) || (tileStepX == -1 && (xIntercept >= x))))
        {
            somethingDone = true;
            y += tileStepY;
            if(IsWall(xIntercept, y, ra))
            {
                hitHoriz      = true;
                rx            = xIntercept;
                _hitOffset    = xIntercept;
                _hitDirection = 0;
                ry            = y + (tileStepY == -1 ? 1 : 0);
                break;
            }
            xIntercept += xStep;
        }
    } while((!hitHoriz && !hitVert) && somethingDone);

    if(!somethingDone)
    {
        return 0;
    }

    float dx = rx - px;
    float dy = ry - py;
    return sqrt(dx * dx + dy * dy);
}

void RayCasterFloat::Trace(
    uint16_t screenX, uint8_t* screenY, uint8_t* textureNo, uint8_t* textureX, uint16_t* textureY, uint16_t* textureStep)
{
    float da = ((int16_t)screenX - SCREEN_WIDTH / 2) * M_PI * FOV / (SCREEN_WIDTH * 4);
    float d2 = Distance(_playerX, _playerY, _playerA + da);
    float ad = d2 * cos(da);
    float dum;
    *textureX    = (uint8_t)(256.0f * modff(_hitOffset, &dum));
    *textureNo   = _hitDirection;
    *textureY    = 0;
    *textureStep = 0;
    if(ad > 0)
    {
        *screenY = INV_FACTOR / ad;
        auto txs = (*screenY * 2.0f);
        if(txs != 0)
        {
            *textureStep = (256 / txs) * 256;
            if(txs > SCREEN_HEIGHT)
            {
                auto ino  = (txs - SCREEN_HEIGHT) / 2;
                *textureY = ino * (256 / txs) * 256;
            }
        }
    }
    else
    {
        *screenY = 0;
    }
}

void RayCasterFloat::Start(uint16_t playerX, uint16_t playerY, int16_t playerA)
{
    _playerX = (playerX / 1024.0f) * 4.0f;
    _playerY = (playerY / 1024.0f) * 4.0f;
    _playerA = (playerA / 1024.0f) * 2.0f * M_PI;
}

RayCasterFloat::RayCasterFloat() : RayCaster() {}

RayCasterFloat::~RayCasterFloat() {}
