#ifndef NeonMatrix_h
#define NeonMatrix_h

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include <Wire.h>

#define LED_ON 1
#define LED_OFF 0

class NeonMatrix : public Adafruit_GFX {
public:
  NeonMatrix(int16_t w = 8, int16_t h = 8);

  void begin();
  void writeDisplay(void);
  void clear(void);

  uint8_t displaybuffer[8];

  void drawPixel(int16_t x, int16_t y, uint16_t color);
};

#endif // NeonMatrix_h