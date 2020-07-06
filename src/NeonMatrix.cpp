#include "Adafruit_GFX.h"
#include "NeonMatrix.h"

#include <SPI.h>

NeonMatrix::NeonMatrix(int16_t w, int16_t h) : Adafruit_GFX(w, h)
{
	this->w = w;
	this->h = h;
	this->panels = w / 8;
	if (w % 8 != 0)
	{
		Serial.println("width not multiple of 8!");
		abort();
	}

	framebuffer = (uint8_t*) calloc(w * h, 1);
	if (!framebuffer)
	{
		Serial.println("calloc framebuffer failed");
		abort();
	}

	shiftdata = (uint8_t*) calloc(w, 1);
	if (!shiftdata)
	{
		Serial.println("calloc shiftdata failed");
		abort();
	}
}

void NeonMatrix::begin() 
{
	pinMode(23, OUTPUT);

	pinMode(22, OUTPUT);

	pinMode(18, OUTPUT);
	pinMode(19, OUTPUT);

	digitalWrite(23, LOW);
}

void NeonMatrix::writeDisplay(void)
{
	memset(shiftdata, 0, this->w);
	for (uint8_t x = 0; x < this->w; x++)
	{
		for (uint8_t y = 0; y < this->h; y++)
		{
			if (framebuffer[y * this->w + x])
			{
				shiftdata[x] |= (1 << y);
			}
		}
	}
	// debug, dump hex to serial console.
	/*for (uint16_t i = 0; i < this->w; i++)
	{
		char buffer[3];
		sprintf(buffer, "%02X", shiftdata[i]);
		Serial.print(buffer);
	}
	Serial.println();
	
	while (!Serial.available()){}
	Serial.read();
	*/

	// debug, dump utf-8 graphic representation of framebuffer to console
	/*Serial.print("\e[1;1H\e[2J");
	for (uint8_t y = 0; y < this->h; y++)
	{
		for (uint8_t x = 0; x < this->w; x++)
		{
			if (framebuffer[y * this->w + x])
			{
				Serial.print("\xE2\x96\x88");
			}
			else
			{
				Serial.print("\xE2\x96\x91");
			}
		}
		Serial.println();
	}*/

	for (uint16_t i = 0; i < this->w; i++)
	{
		this->shiftOutDELAY(18, 19, LSBFIRST, shiftdata[i]);
	}
	delay(1);

	digitalWrite(22, HIGH);
	delay(1); 
	digitalWrite(22, LOW);
	delay(1);
	// LATCH 22
	// OE 23 




}
void NeonMatrix::shiftOutDELAY(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val) {
    uint8_t i;

    for(i = 0; i < 8; i++) {
        if(bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1 << i)));
        else
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));

        digitalWrite(clockPin, HIGH);
		delayMicroseconds(1);
        digitalWrite(clockPin, LOW);
		delayMicroseconds(100);
    }
}


void NeonMatrix::clear(void)
{
	memset(framebuffer, 0, this->w * this->h);
}

void NeonMatrix::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	if ((y < 0) || (y >= this->h))
		return;
	if ((x < 0) || (x >= this->w))
		return;

	framebuffer[y * this->w + x] = !!color; 
}