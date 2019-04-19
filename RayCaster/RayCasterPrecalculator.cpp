#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <sstream>

#include "RayCasterPrecalculator.h"
#include "RayCasterTables.h"

RayCasterPrecalculator::RayCasterPrecalculator() {}

RayCasterPrecalculator::~RayCasterPrecalculator() {}

template <typename T>
void DumpLookupTable(std::ostringstream& dump, T* t, int len)
{
    dump << "{";
    for(int i = 0; i < len; i++)
    {
        dump << (int)t[i];
        if(i == len - 1)
        {
            dump << "};" << std::endl;
        }
        else
        {
            dump << ",";
        }
    }
}

void RayCasterPrecalculator::Precalculate()
{
#ifndef HAS_TABLES

    // replace precalculated lookup tables with these results if you change any constants
    for(int i = 0; i < 256; i++)
    {
        _tan[i]   = static_cast<uint16_t>((256.0f * tan(i * M_PI_2 / 256.0f)));
        _cotan[i] = static_cast<uint16_t>((256.0f / tan(i * M_PI_2 / 256.0f)));
    }
    for(int i = 0; i < 256; i++)
    {
        _sin[i] = static_cast<uint8_t>(256.0f * sin(i / 1024.0f * 2 * M_PI));
        _cos[i] = static_cast<uint8_t>(256.0f * cos(i / 1024.0f * 2 * M_PI));
    }
    for(int i = 0; i < SCREEN_WIDTH; i++)
    {
        int16_t da = static_cast<int16_t>((i - SCREEN_WIDTH / 2) * M_PI * FOV / (SCREEN_WIDTH * 4) / M_PI_2 * 256.0f);
        if(da < 0)
        {
            da += 1024;
        }
        _da[i] = static_cast<uint16_t>(da);
    }
    for(int i = 0; i < 256; i++)
    {
        _neard[i] = static_cast<uint8_t>((INV_FACTOR_INT / (((i << 2) + MIN_DIST) >> 2)) >> 2);
        _fard[i]  = static_cast<uint8_t>((INV_FACTOR_INT / (((i << 5) + MIN_DIST) >> 5)) >> 5);
    }
    for(int i = 0; i < 256; i++)
    {
        auto txn = ((INV_FACTOR_INT / (((i * 4.0f) + MIN_DIST) / 4.0f)) / 4.0f) * 2.0f;
        if(txn != 0)
        {
            _nears[i] = (256 / txn) * 256;
        }
        auto txf = ((INV_FACTOR_INT / (((i * 32.0f) + MIN_DIST) / 32.0f)) / 32.0f) * 2.0f;
        if(txf != 0)
        {
            _fars[i] = (256 / txf) * 256;
        }
    }
    for(int i = 1; i < 256; i++)
    {
        auto txs   = ((INV_FACTOR_INT / (float)(i / 2.0f)));
        auto ino   = (txs - SCREEN_HEIGHT) / 2;
        _shorts[i] = (256 / txs) * 256;
        _shorto[i] = ino * (256 / txs) * 256;
    }

    std::ostringstream dump;

    dump << "const uint16_t LOOKUP_TBL _tan[256] = ";
    DumpLookupTable(dump, _tan, 256);

    dump << "const uint16_t LOOKUP_TBL _cotan[256] = ";
    DumpLookupTable(dump, _cotan, 256);

    dump << "const uint8_t LOOKUP_TBL _sin[256] = ";
    DumpLookupTable(dump, _sin, 256);

    dump << "const uint8_t LOOKUP_TBL _cos[256] = ";
    DumpLookupTable(dump, _cos, 256);

    dump << "const uint8_t LOOKUP_TBL _neard[256] = ";
    DumpLookupTable(dump, _neard, 256);

    dump << "const uint8_t LOOKUP_TBL _fard[256] = ";
    DumpLookupTable(dump, _fard, 256);

    dump << "const uint16_t LOOKUP_TBL _nears[256] = ";
    DumpLookupTable(dump, _nears, 256);

    dump << "const uint16_t LOOKUP_TBL _fars[256] = ";
    DumpLookupTable(dump, _fars, 256);

    dump << "const uint16_t LOOKUP_TBL _shorto[256] = ";
    DumpLookupTable(dump, _shorto, 256);

    dump << "const uint16_t LOOKUP_TBL _shorts[256] = ";
    DumpLookupTable(dump, _shorts, 256);

    dump << "const uint16_t LOOKUP_TBL _da[SCREEN_WIDTH] = ";
    DumpLookupTable(dump, _da, SCREEN_WIDTH);

    std::cout << dump.str() << std::endl;
#endif // ! HAS_TABLES
}
