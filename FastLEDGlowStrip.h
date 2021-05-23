#ifndef FastLEDGlowStrip_h
#define FastLEDGlowStrip_h

#include <FastLED.h>
#include "GlowStrip.h"
#include "FastLED_RGBW.h"
#include "Arduino.h"

class FastLEDGlowStrip : public GlowStrip {
public:
  FastLEDGlowStrip(int n, CRGBW* l, FRGBW* c) : GlowStrip(n,c) {
      leds = l;

  };

  void show() {

    //long start_t = millis();
    for( int i = 0; i < numLeds; i++ ) {
      leds[i] = toCRGBW(current[i]);
    }
    //long convert_t = millis();
    FastLED.show();
    //long show_t = millis();
    //Serial.print("Time taken... Convert: ");Serial.print(convert_t-start_t);
    //Serial.print(", Show: ");Serial.print(show_t-convert_t);
    //Serial.print(", Total Display: ");Serial.println(show_t-start_t);
  };

  CRGBW toCRGBW(FRGBW c) {
    int ri = (int)(c.r*255.0);
    int gi = (int)(c.g*255.0);
    int bi = (int)(c.b*255.0);
    int wi = (int)(c.w*255.0);
    return CRGBW(ri, gi, bi, wi );
  }

protected:
  CRGBW* leds;
};


#endif
