#ifndef __ZUNO_ST7735__
#define __ZUNO_ST7735__

#include "Arduino.h"
#include "SPI.h"
#include "ZUNO_GFX.h"

/*
	конструктор
		записать
*/

class ZUNO_ST7735 : public ZUNO_GFX
{
	public:
		ZUNO_ST7735(uint16_t width, uint16_t height, SPIClass *spi,
				uint8_t i2caddr = I2C_SCREEN_ADDRESS)
		, uint8_t cs,
};

#endif