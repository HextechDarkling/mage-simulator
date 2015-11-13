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
//NOT CURRENTLY TRUE: Signals a start before transmitting data
//NOT CURRENTLY TRUE: Signals a stop condition after transmit if stop is true
//CURRENT IMPLEMENTATION IS BLOCKING
void i2c_tx_byte(unsigned char data);

//Transmits multiple bytes on the I2C bus
//Signals a start before transmitting
//Signals a stop condition after transmit if stop is true
//void i2c_tx_buffer(unsigned char *buffer, unsigned int count, bool stop);

//Receives a single byte from the I2C bus
//CURRENT IMPLEMENTATION IS BLOCKING
unsigned char i2c_rx_byte(void);

//Send a start condition, slave address, and read/write bit on the I2C bus
//True for read, false for write
void i2c_start(bool read);

//Send a stop condition on the I2C bus
void i2c_stop(void);

#endif /* I2C_H_ */
