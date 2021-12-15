/*********************************************************************
 *  Filename : SSD1306.c
 *
 *  Description :
 *       This file contains the implementation for the SSD1306 OLED
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

#include "SSD1306.h"
#include <avr/pgmspace.h>

/* 
 * Function: SSD1306_Init
 * Purpose : Initialize the SSD1306 OLED Controller
 */
void SSD1306_Init(void) {
    I2C_init();                           // Initialize the I2C hardware
    /* Initialization sequence for OLED SSD1306 driver IC */
    I2C_start(OLED_I2C_SLAVE_ADDRESS);    // Let the SSD1306 know we are talking to it
    I2C_write(0x80); I2C_write(0x8D);     // Enable charge pump
    I2C_write(0x80); I2C_write(0x14);  // 
    I2C_write(0x80); I2C_write(0xAF);     // Turn on the display
    I2C_write(0x80); I2C_write(0x20);     // Select Horizontal addressing mode
    I2C_write(0x80); I2C_write(0x00);     // 
    I2C_write(0x80); I2C_write(0x40);     // map COM0 to ROW0 of the display
    I2C_stop();                           // Once all init sequence is done, send STOP
}

/* 
 * Function: SSD1306_SetRect
 * Purpose : Uses the page and column set commands to mark a rectangle of drawing
 * Notes   : parameter x & width is in pixels (0-127), and y & height is in pages (0-7)
 */
void SSD1306_SetRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    I2C_start(OLED_I2C_SLAVE_ADDRESS);    // Let the SSD1306 know we are talking to it
    I2C_write(0x80); I2C_write(0x21);     // Send ColSet command
    I2C_write(0x80); I2C_write(x);        // Starting Column
    I2C_write(0x80); I2C_write(x+width);  // Ending Column
    I2C_write(0x80); I2C_write(0x22);     // Send RowSet command
    I2C_write(0x80); I2C_write(y);        // Starting Row
    I2C_write(0x80); I2C_write(y+height); // Ending Row
    I2C_stop();                           // Once all init sequence is done, send STOP
}

/* 
 * Function: SSD1306_DrawGlyph
 * Purpose : Uses the SetRect function to set the rectangle for the glyph
 *           and also puts the glyph on the screen
 * Notes   : parameter x & width is in pixels (0-127), and y & height is in pages (0-7)
 *           data is not checked for the legth, it is expected to be of width*height
 */
void SSD1306_DrawGlyph(uint8_t x, uint8_t y, uint8_t width, uint8_t height,uint8_t isprogmem, const uint8_t* data) {
    SSD1306_SetRect(x,y,width-1,height-1);    // Set the rectangle to make place for the glyph
    I2C_start(OLED_I2C_SLAVE_ADDRESS);    // Tell the controller we are talking to it
    I2C_write(0x40);                      // Tell the controller we are sending data now
    uint8_t counter;
    for(uint16_t idx=0, counter=0; idx<(width*height); idx++, counter++) {
       I2C_write(isprogmem?pgm_read_byte(data+idx):(*(data+idx))); // Send the data
       if(counter==24){
               I2C_stop();                           // we are done with sending the data
               I2C_start(OLED_I2C_SLAVE_ADDRESS);    // Tell the controller we are talking to it
               I2C_write(0x40);                      // Tell the controller we are sending data now
	       counter=0;
       }
    }
    I2C_stop();                           // we are done with sending the data
}

/* 
 * Function: SSD1306_Clear
 * Purpose : Clears the screen
 */
void SSD1306_Clear(void) {
    SSD1306_SetRect(0,0,127,7);
    I2C_start(OLED_I2C_SLAVE_ADDRESS);    // Tell the controller we are talking to it
    I2C_write(0x40);                      // Tell the controller we are sending data now
    for(uint16_t idx=0; idx<1024; idx++)
        I2C_write(0x00);                  // Just send 0's
    I2C_stop();                           // We are done clearing the screen
}

/* 
 * Function: SSD1306_Clear
 * Purpose : Draws a USB logo at the center of the display, primarily will be used by our bootloader
 */
const __attribute__((section(".display.ro"))) uint8_t usb_logo[] = {
        0x00, 0xC0, 0x24, 0x2E, 0xFF, 0x4E, 0x44, 0x80, 0x00,  // In first row
        0x02, 0x07, 0x22, 0x60, 0xFF, 0x60, 0x2C, 0x0F, 0x0C   // In sercond row
};
 
void USBLogo(void) {
   SSD1306_Init();                       // Initialize the display
    SSD1306_Clear();                      // Clear the display
    SSD1306_DrawGlyph(60,3,9,2,1,usb_logo); // Draw the glyph
}
