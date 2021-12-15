#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#define KEYPAD_DIR_PORT DDRD
#define KEYPAD_PORT     PIND
#define KEYPAD_PORT_OUT PORTD
#define KEYPAD_BTN1_BIT 3  // PWR
#define KEYPAD_BTN2_BIT 5  // PROG
#define KEYPAD_BTN3_BIT 6  // UP
#define KEYPAD_BTN4_BIT 7  // DOWN
#define KEYPAD_PWR_BIT  KEYPAD_BTN1_BIT

#define CAMERA_DIR_PORT   DDRC
#define CAMERA_PORT       PORTC
#define CAMERA_1_BIT      2
#define CAMERA_2_BIT      3

#define POWER_LATCH_DIR_PORT  DDRB
#define POWER_LATCH_PORT      PORTB
#define POWER_LATCH_BIT       0

#endif /* ! __HARDWARE_H__ */
