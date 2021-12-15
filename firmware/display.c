#include <stdint.h>
#include "display.h"
#include "glyphs.h"

void SSD1306_Init(void);
void SSD1306_SetRect(uint8_t, uint8_t, uint8_t, uint8_t);
void SSD1306_DrawGlyph(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, const uint8_t*);
void SSD1306_Clear(void);

static char invalid;

void invalidateDisplay(void){
   invalid = 1;
}

void initDisplay(void) {
   SSD1306_Init(); 
   SSD1306_Clear();
   invalid = 1;
}

void clearDisplay(void) {
   SSD1306_Clear();
}

void draw_time(uint8_t hh,uint8_t mm, uint8_t ss) {
  SSD1306_DrawGlyph(  12    ,0,13,3,0,timer_glyphs[hh/10]);
  SSD1306_DrawGlyph(  25    ,0,13,3,0,timer_glyphs[hh%10]);
  SSD1306_DrawGlyph(  38    ,0,13,3,0,timer_glyphs[10]);
  SSD1306_DrawGlyph(  51    ,0,13,3,0,timer_glyphs[mm/10]);
  SSD1306_DrawGlyph(  64    ,0,13,3,0,timer_glyphs[mm%10]);
  SSD1306_DrawGlyph(  77    ,0,13,3,0,timer_glyphs[10]);
  SSD1306_DrawGlyph(  90    ,0,13,3,0,timer_glyphs[ss/10]);
  SSD1306_DrawGlyph(  103   ,0,13,3,0,timer_glyphs[ss%10]);
}

extern void drawScreen (void);

void displayPoll(void){
  if(invalid) drawScreen();
  invalid = 0;
}
