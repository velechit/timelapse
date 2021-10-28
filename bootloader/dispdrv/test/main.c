/* This is for testing only */

#include "SSD1306.h"
#include <util/delay.h>

int main(void){
   DDRD |= _BV(5);
   PORTD |= _BV(5);
   USBLogo(); // Show the logo
   while(1){
       PORTD ^= _BV(5);
       _delay_ms(250);
   }  // Wait for ever, blinking a test LED @ PORT D5
}
