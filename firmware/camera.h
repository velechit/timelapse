#ifndef __CAMERA_H__
#define __CAMERA_H__

typedef enum {
   CAM_MODE_FOCUS_SHUTTER_BULB = 1,
   CAM_MODE_FOCUS_SHUTTER_ONESHOT,
   CAM_MODE_PRE_FOCUSED_BULB,
   CAM_MODE_PRE_FOCUSED_ONESHOT
} cammode_t;

void set_focus_duration(uint16_t millis);
void set_shutter_duration(uint16_t millis);
void set_focus_shutter_latency(uint16_t millis);
void set_mode(const cammode_t mode); 

void shutter(void);
void initCamera(void);

#endif /* ! __CAMERA_H__ */
