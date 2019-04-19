#include <Arduino.h>

#include "RayCaster.h"
#include "RayCasterData.h"
#include "RayCasterFixed.h"
#include "ST7735R_TFT.h"

int main(void)
{
    init();
    ST7735R_Begin();

    BEGIN_TFT();
    ST7735R_FillRect(0, 0, ST7735R_WIDTH - 1, ST7735R_HEIGHT - 1, 0, 0, 0);

    RayCasterFixed rayCaster;
    int16_t        playerA = 0;
    uint16_t       playerX = 23 << 8;
    uint16_t       playerY = 7 << 8;
    uint8_t        textureNo, textureX, screenY;
    uint16_t       textureY, textureStep;
    for(;;)
    {
        rayCaster.Start(playerX, playerY, playerA);

        ST7735R_BEGIN_TRANSACTION();
        BEGIN_TFT();

        ST7735R_BeginRect(0, 0, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1);
        for(uint8_t x = 0; x < SCREEN_WIDTH; x++)
        {
            rayCaster.Trace(x, &screenY, &textureNo, &textureX, &textureY, &textureStep);

            // ceiling
            const uint8_t outerHeight = HORIZON_HEIGHT - screenY;
            for(uint8_t y = 0; y < outerHeight; y++)
            {
                ST7735R_PushPixel_U16(0, 0x7f);
            }

            // wall
            const uint8_t   wallHeight     = screenY << 1;
            const uint16_t* texturePointer = g_texture565 + (textureX >> 2);
            for(uint8_t y = 0; y < wallHeight; y++)
            {
                // paint texture pixel
                uint16_t texelValue = LOOKUP16(texturePointer, (textureY >> 4) & 0b1111111111000000);

                textureY += textureStep;
                if(textureNo && texelValue)
                {
                    // dark wall
                    texelValue >>= 1;
                    texelValue &= 0b0111101111101111;
                }
                ST7735R_PushPixel_U16(lowByte(texelValue), highByte(texelValue));
            }

            // floor
            for(uint8_t y = 0; y < outerHeight; y++)
            {
                ST7735R_PushPixel_U16(0, 0x6d);
            }
        }
        ST7735R_END_TRANSACTION();
        END_TFT();

        playerA += 10;
        if(playerA > 1024)
        {
            playerA -= 1024;
        }
    }

    return 0;
}
