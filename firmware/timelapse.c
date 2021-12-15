#include <avr/io.h>
#include "display.h"
#include "keypad.h"
#include "system.h"
#include "glyphs.h"


// TODO: Setup Timer0 for 1sec timing
volatile uint8_t hh = 0, mm=0,ss=0;
volatile uint8_t clkcnt = 0;

void incTime(void){
   ss++;
   if(ss>59) {
     ss=0; mm++;
     if(mm>59) {
	mm=0; hh++;
	if(hh>47) hh=0;
     }
   }
}
void decTime(void){
   if(ss==0) {
     if(mm==0) {
       if(hh==0){
	 hh=47;
       } else hh--;
       mm=59;
     } else mm--;
     ss=59;
   } else ss--;
}

void btn1Press (void){
}
void btn2Press (void){
}
void btn3Press (void){
   incTime();
   invalidateDisplay();
}
void btn4Press (void){
   decTime();
   invalidateDisplay();
}
void btn2LongPress (void){
}
void btn3LongPress (void){
}
void btn4LongPress (void){
}

void drawScreen (void){
      draw_time(hh,mm,ss);
}

int main(void)
{
    hh = 0; mm=0;ss=0;
    initSystem();

    while(1){
      keypadPoll();
      displayPoll();
    }
}
