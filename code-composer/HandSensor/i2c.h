/*
 * I2C.h
 *
 *  Created on: Oct 16, 2015
 *      Author: Alex
 */

#ifndef I2C_H_
#define I2C_H_

//Initialize the module
void i2c_init(void);

//Write a single byte to the specified address
void i2c_tx_byte(unsigned char address, unsigned char data);

//Write multiple bytes to the specified address
void i2c_tx_multibyte(unsigned char address, unsigned char* buffer, unsigned char count);

#endif /* I2C_H_ */
