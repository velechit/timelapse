/*********************************************************************
 *  Filename : SSD1306.h
 *
 *  Description :
 *       This file contains the definitions for the SSD1306 OLED
 *       driver. The functions are implemented in a single section
 *       so that the code can be placed in a known memory location
 *       along with the bootloader. This will also reduce the overhead
 *       on the application code, as they need not implement the
 *       driver within the application code
 *
 *  Public functions :
 *       void SSD1306_Init(void);   
 *                        - To initialize the SSD1306 controller
 * 
 *       void SSD1306_SetRect(uint8_t, uint8_t, uint8_t, uint8_t); 
 *                        - To set the data rectangle (page and column)
 * 
 *       void SSD1306_DrawGlyph(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, const uint8_t*);
 *                        - Draws a glyph on the screen
 * 
 *       void SSD1306_Clear(void);
 *                        - Clear the screen
 *       
 *       void USBLogo(void);
 *                        - Show a small USB logo on screen 
 *                          (showing the bootloader in action)
 * 
 * 
 *  Notes :
 *       The display is put in Horizontal addressing mode. Unlike other 
 *       drivers, this driver does not use a ram buffer. So the update
 *       has to be taken care in the caller code, not to corrupt/overwrite
 *       existing locations/graphics. There is no read-modify-write
 *       coded in, this is something may not even be possible with SSD1306
 *       controller. Reading the RAM contents has to be looked into. This
 *       is a future feature. 
 * 
 *       Additionally, the code is sectioned under section name ".display"
 *       This code section, will be placed at a suitable memory location
 *       along with the bootloader.
 * 
 *       There is an additional function in this code page, for the bootloader
 *       to show that bootloader is in action. This is not really a function
 *       for use by applications.
 *
 *  Author : Vishwanath Elechithaya B S (elechi@gmail.com)
 *  Date   : Sun Oct 17 2021
 *
 */

#ifndef __SSD1306_H__
#define __SSD1306_H__

#include "i2c.h"

#define OLED_I2C_SLAVE_ADDRESS          0x3C

void __attribute__((section(".display"))) SSD1306_Init(void);
void __attribute__((section(".display"))) SSD1306_SetRect(uint8_t, uint8_t, uint8_t, uint8_t);
void __attribute__((section(".display"))) SSD1306_DrawGlyph(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, const uint8_t*);
void __attribute__((section(".display"))) SSD1306_Clear(void);

void __attribute__((section(".display"))) USBLogo(void);

#endif


