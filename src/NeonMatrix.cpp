#include "Adafruit_GFX.h"
#include "NeonMatrix.h"

#include <SPI.h>

NeonMatrix::NeonMatrix(int16_t w, int16_t h) : Adafruit_GFX(w, h) {}

#ifndef _swap_int16_t
#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  } ///< 16-bit var swap
#endif

void NeonMatrix::begin() 
{
    
}

void NeonMatrix::writeDisplay(void)
{
    Serial.print("\e[1;1H\e[2J");
    for (uint8_t y = 0; y < 8; y++)
    {
        for (uint8_t x = 0; x < 8; x++)
        {
            if (displaybuffer[y] & (1 << x))
            {
                Serial.print("#");
            }
            else
            {
                Serial.print(" ");
            }
        }
        Serial.println();
    }
}

void NeonMatrix::clear(void) {
  for (uint8_t i = 0; i < 8; i++) {
    displaybuffer[i] = 0;
  }
}


void NeonMatrix::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((y < 0) || (y >= 8))
    return;
  if ((x < 0) || (x >= 8))
    return;

 // check rotation, move pixel around if necessary
  switch (getRotation()) {
  case 1:
    _swap_int16_t(x, y);
    x = 8 - x - 1;
    break;
  case 2:
    x = 8 - x - 1;
    y = 8 - y - 1;
    break;
  case 3:
    _swap_int16_t(x, y);
    y = 8 - y - 1;
    break;
  }

  /* // wrap around the x
  x += 7;
  x %= 8;*/

  if (color) {
    displaybuffer[y] |= 1 << x;
  } else {
    displaybuffer[y] &= ~(1 << x);
  }
}