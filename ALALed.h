#ifndef ALALed_h
#define ALALed_h

#include "ALA.h"
void sparkle(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void sparkle2(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void strobo(Adafruit_NeoPixel &strip, AlaColor col, int speed);
void pixelShiftRight(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void pixelShiftLeft(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void pixelBounce(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void pixelSmoothShiftRight(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void pixelSmoothShiftLeft(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void comet(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void cometCol(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void pixelSmoothBounce(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void larsonScanner(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void larsonScanner2(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void fadeIn(Adafruit_NeoPixel &strip, AlaColor col, int speed);
void fadeOut(Adafruit_NeoPixel &strip, AlaColor col, int speed);
void fadeInOut(Adafruit_NeoPixel &strip, AlaColor col, int speed);
void glow(Adafruit_NeoPixel &strip, AlaColor col, int speed);
void fadeColors(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void pixelsFadeColors(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void fadeColorsLoop(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void cycleColors(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void movingBars(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void movingGradient(Adafruit_NeoPixel &strip, AlaPalette palette, int speed);
void fire(Adafruit_NeoPixel &strip, AlaPalette palette);
void fillPixel(Adafruit_NeoPixel &strip, AlaColor c, int speed);
void fillPixelPalette(Adafruit_NeoPixel &strip, AlaColor c, AlaPalette palette, int speed);
void fillPixelRandom(Adafruit_NeoPixel &strip, int speed);
void chase(Adafruit_NeoPixel &strip, AlaColor col,AlaColor col2, int speed);
void chase2(Adafruit_NeoPixel &strip, int speed);
void blink(Adafruit_NeoPixel &strip, AlaColor col, AlaColor col2, int speed);
void blinkalt(Adafruit_NeoPixel &strip, AlaColor col, AlaColor col2, int speed);
#endif
