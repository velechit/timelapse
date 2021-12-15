#include <avr/io.h>
#include "power.h"
#include "hw.h"

void waitPowerOn(void) {
    if(MCUCSR!=0) POWER_LATCH_PORT &= (~_BV(POWER_LATCH_BIT)); // turn off
}

void powerOn(void){
   POWER_LATCH_DIR_PORT |= _BV(POWER_LATCH_BIT);
   POWER_LATCH_PORT     |= _BV(POWER_LATCH_BIT);
}

void powerOff(void){
    while(KEYPAD_PORT & _BV(KEYPAD_BTN1_BIT)); // wait till the btn is released
    while(1) POWER_LATCH_PORT     &= (~_BV(POWER_LATCH_BIT));
}

