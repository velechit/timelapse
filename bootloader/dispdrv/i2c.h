/*********************************************************************
 *  Filename : i2c.h
 *
 *  Description :
 *       This file will define basic functions required for I2C
 *       Communication usin TWI bus of Atmel Controllers
 *
 *  Public functions :
 *       void I2C_init(void);     - Initializes the TWI Hardware
 *       void I2C_start(uint8_t); - Sends a START condition (+ slave address)
 *       void I2C_write(uint8_t); - Write out a byte on TWI interface
 *       void I2C_stop(void);     - Sends a STOP condition
 *
 *  Notes :
 *       Only needed 4 functions on I2C, to create the start/stop 
 *       conditions and to send the data. Additionally to initialize
 *       the TWI Hadware. We shall use the TWI clock @ 400kHz
 *
 *       All the I2C functions will be inline functions.
 *
 *  Author : Vishwanath Elechithaya B S (elechi@gmail.com)
 *  Date   : Sun Oct 17 2021
 *
 */

#ifndef __I2C_H__
#define __I2C_H__

#include <util/twi.h>
#include <inttypes.h>

/* 
 * Function: I2C_init
 * Purpose : Initialize the TWI Hardware
 */
static __attribute__((section(".display"))) inline void I2C_init(void) {
    TWSR = 0x00; TWBR = 0x0C;   // this will configure TWI to use 400kHz clock with 12MHz sys clock
    TWCR = _BV(TWEN);           // Enable the TWI hadware
}

/* 
 * Function: I2C_start
 * Purpose : Generate the START condition on the TWI bus
 */
static __attribute__((section(".display"))) inline void I2C_start(uint8_t slaveAddress) {
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN) ;        // Send a START condition
    while(!(TWCR & _BV(TWINT))) ;                       // Wait for START to be on the bus

    TWDR = (slaveAddress << 1) | TW_WRITE ;             // Put the slave Address on the bus
    TWCR = _BV(TWINT) | _BV(TWEN) ;                     // Start the address transmission
    while(!(TWCR & _BV(TWINT))) ;                       // Wait for the address to be transmitted
}

/* 
 * Function: I2C_write
 * Purpose : Sends one byte of data on the TWI bus
 */
static __attribute__((section(".display"))) inline void I2C_write(uint8_t data) {
    TWDR = data ;                        // Put the data on the DR
    TWCR = _BV(TWINT) | _BV(TWEN) ;      // Send the data on the TWI bus
    while(!(TWCR & _BV(TWINT))) ;        // Wait for the data to be transmitted
}

/* 
 * Function: I2C_stop
 * Purpose : Generates STOP condition on the TWI bus
 */
static __attribute__((section(".display"))) inline void I2C_stop(void) {
    TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN) ;        // Ask the TWI hardware to generate a stop bit
}

#endif /* ! __I2C_H__ */


