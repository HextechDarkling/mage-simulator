/*
 * i2c.h
 *
 *  Created on: Nov 12, 2015
 *      Author: Alex
 */

#ifndef I2C_H_
#define I2C_H_

#include <msp430.h>
#include <stdbool.h>

//Initialize the module
void i2c_init(void);

//Set the address of the slave to communicate with
void i2c_set_slave_address(unsigned int address);

//Transmit a single byte on the I2C bus
//Signals a stop condition after transmit if stop is true
void i2c_tx_byte(unsigned char data, bool stop);

//Transmits multiple bytes on the I2C bus
//Signals a stop condition after transmit if stop is true
void i2c_tx_buffer(unsigned char *buffer, unsigned int count, bool stop);

#endif /* I2C_H_ */
