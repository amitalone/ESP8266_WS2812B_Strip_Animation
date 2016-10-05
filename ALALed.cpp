#include "Arduino.h"
#include "ALA.h"
#include <Adafruit_NeoPixel.h>

long animStartTime = millis();
int oldt =0;
int tCycle =0;
int cx =0;


void sparkle(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
    int p = speed/100;
  for(int x=0; x<strip.numPixels(); x++)
    {
        AlaColor col = palette.colors[random(palette.numColors)].scale(random(p)==0);
        strip.setPixelColor(x  ,  strip.Color(col.r, col.g, col.b));
    }
    strip.show();
}

void sparkle2(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int p = speed/10;
  for(int x=0; x<strip.numPixels(); x++)
    {
      if(random(p)==0) {
        AlaColor col = palette.colors[random(palette.numColors)];
        strip.setPixelColor(x  ,  strip.Color(col.r, col.g, col.b));
      }
      else {
        AlaColor col = AlaColor(strip.getPixelColor(x)).scale(0.88);
        strip.setPixelColor(x  ,  strip.Color(col.r, col.g, col.b));
       }
    }
    strip.show();
}

void strobo(Adafruit_NeoPixel &strip, AlaColor col, int speed)
{
  int t = getStep(animStartTime, speed, ALA_STROBODC);
  
  col = col.scale(t==0);
  for(int x=0; x<strip.numPixels(); x++)
  {
     strip.setPixelColor(x, strip.Color(col.r, col.g, col.b));
  }
  strip.show();
}

void pixelShiftRight(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  int t = getStep(animStartTime, speed, numLeds);
  float tx = getStepFloat(animStartTime, speed, palette.numColors);
  AlaColor c = palette.getPalColor(tx);
  
  for(int x=0; x<numLeds; x++)
  {
    int k = (x==t ? 1:0);
    AlaColor d = c.scale(k);
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
      
  }
  strip.show();
}
void pixelShiftLeft(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  int t = getStep(animStartTime, speed, numLeds);
  float tx = getStepFloat(animStartTime, speed, palette.numColors);
  AlaColor c = palette.getPalColor(tx);
  for(int x=0; x<numLeds; x++)
  {
    int k = ((x==(numLeds-1-t) ? 1:0));
    AlaColor d = c.scale(k);
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
 }
  strip.show();
}

void pixelBounce(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  int t = getStep(animStartTime, speed, 2*numLeds-2);
  float tx = getStepFloat(animStartTime, speed, palette.numColors);
  AlaColor c = palette.getPalColor(tx);
  for(int x=0; x<numLeds; x++)
  {
    int k = x==(-abs(t-numLeds+1)+numLeds-1) ? 1:0;
    AlaColor d = c.scale(k);
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}
void pixelSmoothShiftRight(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  float t = getStepFloat(animStartTime, speed, numLeds+1);
  float tx = getStepFloat(animStartTime, speed, palette.numColors);
  AlaColor c = palette.getPalColor(tx);
  
  for(int x=0; x<numLeds; x++)
  {
    float k = max(0, (-abs(t-1-x)+1));
    AlaColor d = c.scale(k);
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}
void pixelSmoothShiftLeft(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  float t = getStepFloat(animStartTime, speed, numLeds+1);
  float tx = getStepFloat(animStartTime, speed, palette.numColors);
  AlaColor c = palette.getPalColor(tx);
  
  for(int x=0; x<numLeds; x++)
  {
    float k = max(0, (-abs(numLeds-t-x)+1));
    AlaColor d = c.scale(k);
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}

void comet(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  float l = numLeds/2;  // length of the tail
  float t = getStepFloat(animStartTime, speed, 2*numLeds-l);
  float tx = getStepFloat(animStartTime, speed, palette.numColors);
  AlaColor c = palette.getPalColor(tx);
  
  for(int x=0; x<numLeds; x++)
  {
    float k = constrain( (((x-t)/l+1.2f))*(((x-t)<0)? 1:0), 0, 1);
    AlaColor d = c.scale(k);
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
   strip.show();
}

void cometCol(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  float l = numLeds/2;  // length of the tail
  float t = getStepFloat(animStartTime, speed, 2*numLeds-l);
  AlaColor c;
  for(int x=0; x<numLeds; x++)
  {
    float tx = mapfloat(max(t-x, 0), 0, numLeds/1.7, 0, palette.numColors-1);
    c = palette.getPalColor(tx);
    float k = constrain( (((x-t)/l+1.2f))*(((x-t)<0)? 1:0), 0, 1);
    AlaColor d = c.scale(k);
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}

void pixelSmoothBounce(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  float t = getStepFloat(animStartTime, speed, 2*numLeds-2);
  AlaColor c = palette.getPalColor(getStepFloat(animStartTime, speed, palette.numColors));

  for(int x=0; x<numLeds; x++)
  {
    float k = constrain((-abs(abs(t-numLeds+1)-x)+1), 0, 1);
    AlaColor d = c.scale(k);
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}

void larsonScanner(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  float l = numLeds/4;
  float t = getStepFloat(animStartTime, speed, 2*numLeds-2);
  AlaColor c = palette.getPalColor(getStepFloat(animStartTime, speed, palette.numColors));

  for(int x=0; x<numLeds; x++)
  {
    float k = constrain((-abs(abs(t-numLeds+1)-x)+l), 0, 1);
    AlaColor d = c.scale(k);
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}
void larsonScanner2(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  float l = numLeds/4;  // 2>7, 3-11, 4-14
  float t = getStepFloat(animStartTime, speed, 2*numLeds+(l*4-1));
  AlaColor c = palette.getPalColor(getStepFloat(animStartTime, speed, palette.numColors));
  for(int x=0; x<numLeds; x++)
  {
    float k = constrain((-abs(abs(t-numLeds-2*l)-x-l)+l), 0, 1);
    AlaColor d = c.scale(k);
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}
void fadeIn(Adafruit_NeoPixel &strip, AlaColor col, int speed)
{
  int numLeds = strip.numPixels();
  float s = getStepFloat(animStartTime, speed, 1);
  AlaColor d = col.scale(s);
  
  for(int x=0; x<numLeds; x++)
  {
     strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}
void fadeOut(Adafruit_NeoPixel &strip, AlaColor col, int speed)
{
  int numLeds = strip.numPixels();
  float s = getStepFloat(animStartTime, speed, 1);
  AlaColor d =col.scale(1-s);
  
  for(int x=0; x<numLeds; x++)
  {
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}
void fadeInOut(Adafruit_NeoPixel &strip, AlaColor col, int speed)
{
  int numLeds = strip.numPixels();
  float s = getStepFloat(animStartTime, speed, 2) - 1;
  AlaColor d = col.scale(abs(1-abs(s)));

  for(int x=0; x<numLeds; x++)
  {
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}
void glow(Adafruit_NeoPixel &strip, AlaColor col, int speed)
{
  int numLeds = strip.numPixels();
  float s = getStepFloat(animStartTime, speed, TWO_PI);
  float k = (-cos(s)+1)/2;
  for(int x=0; x<numLeds; x++)
  {
    AlaColor d = col.scale(k);
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}

void fadeColors(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  float t = getStepFloat(animStartTime, speed, palette.numColors-1);
  AlaColor d = palette.getPalColor(t);
  for(int x=0; x<numLeds; x++)
  {
   strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}
void pixelsFadeColors(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  float t = getStepFloat(animStartTime, speed, palette.numColors);

  for(int x=0; x<strip.numPixels(); x++)
  {
    AlaColor d = palette.getPalColor(t+7*x);
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}
void fadeColorsLoop(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  float t = getStepFloat(animStartTime, speed, palette.numColors);
  AlaColor d = palette.getPalColor(t);
  for(int x=0; x<strip.numPixels(); x++)
  {
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}
void cycleColors(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int t = getStep(animStartTime, speed, palette.numColors);

  for(int x=0; x<strip.numPixels(); x++)
  {
    AlaColor d = palette.colors[t];
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
   strip.show();
}

void movingBars(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  int t = getStep(animStartTime, speed, numLeds);

  for(int x=0; x<numLeds; x++)
  {
    AlaColor d = palette.colors[(((t+x)*palette.numColors)/numLeds)%palette.numColors];
    strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}

void movingGradient(Adafruit_NeoPixel &strip, AlaPalette palette, int speed)
{
  int numLeds = strip.numPixels();
  float t = getStepFloat(animStartTime, speed, numLeds);
  for(int x=0; x<numLeds; x++)
  {
    AlaColor d = palette.getPalColor((float)((x+t)*palette.numColors)/numLeds);
     strip.setPixelColor(x, strip.Color(d.r, d.g, d.b));
  }
  strip.show();
}
void fire(Adafruit_NeoPixel &strip, AlaPalette palette)
{
  int numLeds = strip.numPixels();
    #define COOLING  600
    #define SPARKING 120

    static byte *heat = NULL;
  
  if (heat==NULL)
        heat = new byte[numLeds];

    int rMax = (COOLING / numLeds) + 2;
  for(int i=0; i<numLeds; i++)
  {
      heat[i] = max(((int)heat[i]) - random(0, rMax), 0);
    }
  
    for(int k=numLeds-1; k>=3; k--)
  {
      heat[k] = ((int)heat[k - 1] + (int)heat[k - 2] + (int)heat[k - 3] ) / 3;
    }
    
    if(random(255) < SPARKING)
  {
      int y = random(7);
      heat[y] = min(heat[y] + random(160, 255), 255);
    }

    for(int j=0; j<numLeds; j++)
  {
      float colorindex = (float)(heat[j] * (palette.numColors-1) ) / 256;
      AlaColor d = palette.getPalColor(colorindex);
      strip.setPixelColor(j, strip.Color(d.r, d.g, d.b));
    }
    strip.show();
}

void fillPixelRandom(Adafruit_NeoPixel &strip, int speed) {
  int t = getStep(animStartTime, speed , strip.numPixels());
  strip.setPixelColor(random(strip.numPixels()) ,  strip.Color(random(255), random(255), random(255)));
  strip.show();
  if(t == strip.numPixels() -1) {
    for(int x=0; x<strip.numPixels(); x++)
    {
      strip.setPixelColor(x , 0);
    }
    strip.show();
  }
}

void fillPixelPalette(Adafruit_NeoPixel &strip, AlaColor c, AlaPalette palette, int speed)
{
  int t = getStep(animStartTime, speed , strip.numPixels());
  if(oldt != t) {
    oldt = t;
   if(oldt == strip.numPixels() -1) {
        tCycle++;
        if(tCycle >= strip.numPixels() -1) {
        tCycle =0;
       }
    }
  }

   for(int x=0; x<strip.numPixels() -tCycle; x++)
    {
        int k = (x==t ? 1:0);
        AlaColor col = c.scale(k);
        if(x == strip.numPixels() -tCycle -1) {
          col = palette.colors[random(palette.numColors)];
        }
        
        strip.setPixelColor(x  ,  strip.Color(col.r, col.g, col.b));
    }
    strip.show();
}
void fillPixel(Adafruit_NeoPixel &strip, AlaColor c, int speed) 
{
  int t = getStep(animStartTime, speed , strip.numPixels());
  if(oldt != t) {
    oldt = t;
   if(oldt == strip.numPixels() -1) {
        tCycle++;
        if(tCycle >= strip.numPixels() -1) {
        tCycle =0;
       }
    }
  }

   for(int x=0; x<strip.numPixels() -tCycle; x++)
    {
        int k = (x==t ? 1:0);
        if(x == strip.numPixels() -tCycle -1) {
          k =1;
        }
        AlaColor col = c.scale(k);
        strip.setPixelColor(x  ,  strip.Color(col.r, col.g, col.b));
    }
    strip.show();
}

void chase(Adafruit_NeoPixel &strip, AlaColor col, AlaColor col2, int speed) {
  int t = getStep(animStartTime, speed , strip.numPixels());
  for (int i = 0; i < strip.numPixels(); i++)
   {
       if (i == t)
        {
           for (int j = i; j <i+ 4; j++)
            {
               strip.setPixelColor(j, strip.Color(col.r, col.g, col.b));
               strip.setPixelColor(j -3, strip.Color(col2.r, col2.g, col2.b));
            }
        }
   }
    strip.show();
}

void chase2(Adafruit_NeoPixel &strip, int speed) {
  int t = getStep(animStartTime, speed , strip.numPixels());
  for (int i = 0; i < strip.numPixels(); i++)
   {
      int r0 =  random(0, 255);
      int g0 =  random(0, 255);
      int b0 =  random(0, 255);
       if (i == t)
        {
           for (int j = i; j <i+ 4; j++)
            {
               strip.setPixelColor(j, strip.Color(r0, g0, b0));
               strip.setPixelColor(j -4, 0);
            }
        }
   }
    strip.show();
}
void blink(Adafruit_NeoPixel &strip, AlaColor col, AlaColor col2, int speed) {
   int t = getStep(animStartTime, speed , strip.numPixels());
  for (int i = 0; i < strip.numPixels(); i++)
   {
       if ((t+1) % 2 == 0)
        {
           strip.setPixelColor(i, strip.Color(col.r, col.g, col.b));
           
        }
        else
        {
           strip.setPixelColor(i, strip.Color(col2.r, col2.g, col2.b));
        }
    }
   strip.show();
}
void blinkalt(Adafruit_NeoPixel &strip, AlaColor col, AlaColor col2, int speed) {
  int t = getStep(animStartTime, speed , strip.numPixels());
   for (int i = 0; i < strip.numPixels(); i++)
   {
       if ((t+i) % 2 == 0)
        {
           strip.setPixelColor(i, strip.Color(col.r, col.g, col.b));
           
        }
        else
        {
           strip.setPixelColor(i, strip.Color(col2.r, col2.g, col2.b));
        }
    }
   strip.show();
}

