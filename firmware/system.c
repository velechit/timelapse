#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "system.h"
#include "power.h"
#include "display.h"
#include "keypad.h"
#include "camera.h"

void initSystem(void) {
   cli();
   waitPowerOn();
   initDisplay();
   _delay_ms(50);
   keypadInit();
   initCamera();
   powerOn();
   sei();
}

void shutDown(void){
   clearDisplay();
   powerOff();
}
