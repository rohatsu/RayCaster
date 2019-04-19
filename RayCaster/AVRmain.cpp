#include <Arduino.h>

#include "RayCaster.h"
#include "RayCasterFixed.h"
#include "ST7735R_TFT.h"

// Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/ )()) { return 0; }

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void setupUSB() __attribute__((weak));
void setupUSB() { }

void setup()
{
	Serial.begin(9600);
	ST7735R_Begin();
	BEGIN_TFT();
	ST7735R_FillRect(0, 0, ST7735R_WIDTH-1, ST7735R_HEIGHT-1, 0, 0, 0);
	END_SDCARD();
}

int main(void)
{
	init();

	initVariant();
/*
	#if defined(USBCON)
	USBDevice.attach();
	#endif
	*/
	setup();
	
	RayCasterFixed rc;
	const uint8_t c = 0x7f;
	int16_t a = 0;
	uint16_t px = 23 << 8;
	uint16_t py = 7 << 8;
	uint8_t hd = 0;
	uint8_t tn, tx;
	uint8_t d;
	uint16_t ty, ts;
	for(;;)
	{
		a += 10;
		if(a > 1024)
		a -= 1024;
		
		rc.Start(px, py, a);
		
		END_SDCARD();
		ST7735R_BEGIN_TRANSACTION();
		BEGIN_TFT();
		
		ST7735R_BeginRect(0, 0, 127, 159);
		for(uint8_t y = 0; y < 160; y++)
		{
			rc.Trace(y, &d, &tn, &tx, &ty, &ts);

			const uint8_t c = tn ? 0x55 : 0x7f;
			
			for(uint8_t x = 0; x < 64 - d; x++)
			{
				ST7735R_PushPixel_U16(0, 0x7f);
			}

			for(uint8_t x = 0; x < 2 * d; x++)
			{
				ST7735R_PushPixel_U16(c, 0);
			}

			for(uint8_t x = 0; x < 64 - d; x++)
			{
				ST7735R_PushPixel_U16(0, 0x6d);
			}
		}
		ST7735R_END_TRANSACTION();
		END_TFT();
		if (serialEventRun) serialEventRun();
	}

	return 0;
}

