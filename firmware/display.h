#ifndef __DISPLAY_H__
#define __DISPLAY_H__

void invalidateDisplay(void);
void initDisplay(void);
void clearDisplay(void);
void displayPoll(void);


void draw_time(uint8_t hh,uint8_t mm, uint8_t ss);

#endif /* ! __DISPLAY_H__ */
