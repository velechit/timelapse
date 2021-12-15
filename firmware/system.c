#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "system.h"
#include "power.h"
#include "display.h"
#include "keypad.h"

void initSystem(void) {
   cli();
   waitPowerOn();
   initDisplay();
   _delay_ms(50);
   keypadInit();
   powerOn();
   sei();
}

void shutDown(void){
   clearDisplay();
   powerOff();
}
