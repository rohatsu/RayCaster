#pragma once

#include <stdint.h>

class Game
{
private:
    uint8_t* _map;

public:
    uint8_t* CreateMap();
    void     Move(int m, int r);

    float px, py, pa;

    Game();
    ~Game();
};
