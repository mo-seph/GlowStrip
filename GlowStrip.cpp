#include "GlowStrip.h"
#include <math.h>       /* ceil */
#include "Arduino.h"
/* Interface */
void GlowStrip::setRGBW(int num, float r, float g, float b, float w) {
  current[num].r = r;
  current[num].g = g;
  current[num].b = b;
  current[num].w = w;
}

void GlowStrip::setRGBW(int num, FRGBW val) {
  current[num].r = val.r;
  current[num].g = val.g;
  current[num].b = val.b;
  current[num].w = val.w;
}

/* Interface */
void GlowStrip::setRGB(int num, float r, float g, float b) {
  current[num].r = r;
  current[num].g = g;
  current[num].b = b;
}
/* Interface */
void GlowStrip::setW(int num,  float w ) {
  current[num].w = w;
}

void GlowStrip::addRGBW(int num, FRGBW val) {
  current[num].r += min(1.0,val.r);
  current[num].g += min(1.0,val.g);
  current[num].b += min(1.0,val.b);
  current[num].w += min(1.0,val.w);
}




void GlowStrip::spatialInterpolation(PointARGBW from, PointARGBW to) {
  if( from.position > to.position ) {
    PointARGBW tmp = to;
    to = from;
    from = tmp;
  }
  int start = from.position;
  int end = to.position;
  float len = (float)(end-start-1);
  for( int i = start; i < end; i++ ) {
    float rel_pos = ((float)(i - start )) / len;
    float amount = min(max(rel_pos,0.0),1.0);
    setRGBW(i, interpolateRGBW(from.color,to.color,amount));
  }
}

void GlowStrip::glowRGBWRel(AreaRGBW g, bool additive) {
  float start_rel = max(0.0,g.centre-g.width);
  float end_rel = min(1.0,g.centre+g.width);
  int start = max((int)(start_rel*(float)numLeds),0);
  int end = min((int)(end_rel*(float)numLeds) + 1, numLeds);
  int abs_width = end - start - 1;
  float abs_cent = g.centre * numLeds;
  FRGBW base(0,0,0,0);
  for( int i = start; i < end; i++ ) {
    float distance = abs(abs_cent-i);
    float prop_distance = 2 * distance / abs_width;
    float amount = max(1 - prop_distance,0.0);

    if( additive ) addRGBW(i,interpolateRGBW(base,g.color,amount));
    else setRGBW(i,interpolateRGBW(base,g.color,amount));
  }
};
