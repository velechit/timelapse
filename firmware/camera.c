#include <avr/io.h>
#include <util/delay.h>
#include "hw.h"
#include "camera.h"

static cammode_t camera_mode;
static uint16_t focus_duration;
static uint16_t focus_shutter_latency;
static uint16_t shutter_duration;

void set_focus_duration(uint16_t millis){
focus_duration = millis;
}
void set_shutter_duration(uint16_t millis){
shutter_duration = millis;
}
void set_focus_shutter_latency(uint16_t millis){
focus_shutter_latency = millis;
}
void set_mode(const cammode_t mode) {
  camera_mode = mode;
}

void focus(void){
  uint16_t i;
  if(camera_mode == CAM_MODE_PRE_FOCUSED_BULB || camera_mode == CAM_MODE_PRE_FOCUSED_ONESHOT) return;
  CAMERA_PORT |= _BV(CAMERA_1_BIT);
  for(i=focus_duration; i>0;i--) _delay_ms(1);
  CAMERA_PORT &= (~_BV(CAMERA_1_BIT));
}

void shutter(void){
  uint16_t i;
  if(camera_mode == CAM_MODE_FOCUS_SHUTTER_BULB || camera_mode == CAM_MODE_FOCUS_SHUTTER_ONESHOT) focus();
  for(i=focus_shutter_latency;i>0;i--) _delay_ms(1);
  CAMERA_PORT |= _BV(CAMERA_2_BIT);
  if(camera_mode == CAM_MODE_FOCUS_SHUTTER_BULB || camera_mode == CAM_MODE_PRE_FOCUSED_BULB) 
       for(i=shutter_duration;i>0;i--) _delay_ms(1);
  else
       _delay_ms(10);

  CAMERA_PORT &= (~_BV(CAMERA_2_BIT));
}

void initCamera(void) {
  CAMERA_DIR_PORT |= (_BV(CAMERA_1_BIT)|_BV(CAMERA_2_BIT));
  CAMERA_PORT &= (~(_BV(CAMERA_1_BIT)|_BV(CAMERA_2_BIT)));
}

