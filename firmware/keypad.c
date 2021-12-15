#include <avr/io.h>
#include <avr/interrupt.h>
#include "keypad.h"
#include "hw.h"
#include "system.h"

#define KP_MASK (_BV(KEYPAD_BTN1_BIT)| _BV(KEYPAD_BTN2_BIT)| _BV(KEYPAD_BTN3_BIT) | _BV(KEYPAD_BTN4_BIT))

volatile uint8_t key_press,key_state,key_rpt;


#define DEBOUNCE_TIME 10

#define REPEAT_MASK	(_BV(KEYPAD_BTN1_BIT)^_BV(KEYPAD_BTN2_BIT)^_BV(KEYPAD_BTN3_BIT)^_BV(KEYPAD_BTN4_BIT))	// repeat: key1, key2
#define REPEAT_START	50		// after 500ms
#define REPEAT_NEXT	20		// every 200ms

#define readKey() (((~KEYPAD_PORT) & KP_MASK) ^ _BV(KEYPAD_BTN1_BIT))


ISR(TIMER2_OVF_vect){ // to be called every 10 milisecond
  static uint8_t ct0, ct1, rpt;
  uint8_t i;

  i = key_state ^ readKey();		// key changed ?, btn1 is inverted
  ct0 = ~( ct0 & i );			// reset or count ct0
  ct1 = ct0 ^ (ct1 & i);		// reset or count ct1
  i &= ct0 & ct1;			// count until roll over ?
  key_state ^= i;			// then toggle debounced state
  key_press |= key_state & i;		// 0->1: key press detect

  if( (key_state & REPEAT_MASK) == 0 )	// check repeat function
     rpt = REPEAT_START;		// start delay
  if( --rpt == 0 ){
    rpt = REPEAT_NEXT;			// repeat delay
    key_rpt |= key_state & REPEAT_MASK;
  }
}

uint8_t get_key_press( uint8_t key_mask )
{
  cli();					// read and clear atomic !
  key_mask &= key_press;                        // read key(s)
  key_press ^= key_mask;                        // clear key(s)
  sei();
  return key_mask;
}


uint8_t get_key_rpt( uint8_t key_mask )
{
  cli();					// read and clear atomic !
  key_mask &= key_rpt;                        	// read key(s)
  key_rpt ^= key_mask;                        	// clear key(s)
  sei();
  return key_mask;
}


uint8_t get_key_short( uint8_t key_mask )
{
  return get_key_press( ~key_state & key_mask );
}


uint8_t get_key_long( uint8_t key_mask )
{
  return get_key_press( get_key_rpt( key_mask ));
}

extern void btn1Press (void);
extern void btn2Press (void);
extern void btn3Press (void);
extern void btn4Press (void);

extern void btn2LongPress (void);
extern void btn3LongPress (void);
extern void btn4LongPress (void);

void keypadPoll(void) {
    if( get_key_short( _BV(KEYPAD_BTN1_BIT) ))
      btn1Press();
    if( get_key_long( _BV(KEYPAD_BTN1_BIT) ))
      shutDown(); // BTN1 long press always power-off
    if( get_key_short( _BV(KEYPAD_BTN2_BIT) ))
      btn2Press();
    if( get_key_long( _BV(KEYPAD_BTN2_BIT) ))
      btn2LongPress();
    if( get_key_short( _BV(KEYPAD_BTN3_BIT) ))
      btn3Press();
    if( get_key_long( _BV(KEYPAD_BTN3_BIT) ))
      btn3LongPress();
    if( get_key_short( _BV(KEYPAD_BTN4_BIT) ))
      btn4Press();
    if( get_key_long( _BV(KEYPAD_BTN4_BIT) ))
      btn4LongPress();
}


void keypadInit(void){
  key_state=0;
  key_press=0;
  key_rpt = 0;

  KEYPAD_DIR_PORT &=(~KP_MASK); // Make btn pins input
  KEYPAD_PORT_OUT |= (_BV(KEYPAD_BTN2_BIT)| _BV(KEYPAD_BTN3_BIT) | _BV(KEYPAD_BTN4_BIT));

  TIMSK |= _BV(TOIE2);            // Enable timer2 interrupt
  TCCR2 |= _BV(CS22)|_BV(CS21)|_BV(CS20);   // 1/256 prescalar
}

