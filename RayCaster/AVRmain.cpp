#include <Arduino.h>

#include "RayCaster.h"
#include "RayCasterData.h"
#include "RayCasterFixed.h"
#include "ST7735R_TFT.h"

int atexit(void (* /*func*/ )()) { return 0; }

int main(void)
{
	init();

	Serial.begin(9600);
	ST7735R_Begin();
	BEGIN_TFT();
	ST7735R_FillRect(0, 0, ST7735R_WIDTH-1, ST7735R_HEIGHT-1, 0, 0, 0);
	
	RayCasterFixed rc;
	int16_t a = 0;
	uint16_t px = 23 << 8;
	uint16_t py = 7 << 8;
	uint8_t tn, tx, d, hd;
	uint16_t ty, ts;
	for(;;)
	{
		rc.Start(px, py, a);
		
		ST7735R_BEGIN_TRANSACTION();
		BEGIN_TFT();
		
		ST7735R_BeginRect(0, 0, 127, 159);
		for(uint8_t y = 0; y < 160; y++)
		{
			rc.Trace(y, &d, &tn, &tx, &ty, &ts);

			// ceiling
			for(uint8_t x = 0; x < 64 - d; x++)
			{
				ST7735R_PushPixel_U16(0, 0x7f);
			}
			
			// wall
			const uint8_t _tx = tx >> 2;
			for(uint8_t x = 0; x < 2 * d; x++)
			{
				// paint texture pixel
				uint16_t _tv = LOOKUP16(_tex565, (((ty >> 4) & 0b1111111111000000) + _tx));

				ty += ts;
				if (tn == 1 && _tv > 0)
				{
					// dark wall
					_tv >>= 1;
					ST7735R_PushPixel_U16(lowByte(_tv) & 0b11101111, highByte(_tv) & 0b01111011);
				}
				else
				{
					ST7735R_PushPixel_U16(lowByte(_tv), highByte(_tv));
				}
			}

			// floor
			for(uint8_t x = 0; x < 64 - d; x++)
			{
				ST7735R_PushPixel_U16(0, 0x6d);
			}
		}
		ST7735R_END_TRANSACTION();
		END_TFT();
		if (serialEventRun) serialEventRun();
		
		a += 10;
		if(a > 1024)
		a -= 1024;
	}

	return 0;
}
