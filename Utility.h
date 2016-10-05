#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#ifndef Utility_H
#define Utility_H

void allOn(Adafruit_NeoPixel &strip, uint32_t c);


void colorWipe(Adafruit_NeoPixel &strip, uint32_t c, uint8_t wait);
void rainbowFade2White(Adafruit_NeoPixel &strip,uint8_t wait, int rainbowLoops, int whiteLoops);
void whiteOverRainbow(Adafruit_NeoPixel &strip,uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength );
void rainbowCycle(Adafruit_NeoPixel &strip,uint8_t wait);
void rainbow(Adafruit_NeoPixel &strip, uint8_t wait);
void theaterChaseRainbow(Adafruit_NeoPixel &strip, uint8_t wait);
void theaterChase(Adafruit_NeoPixel &strip,uint32_t c, uint8_t wait);

#endif
