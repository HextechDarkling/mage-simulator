/*
 * serial.h
 *
 *  Created on: Oct 6, 2015
 *      Author: Alex
 */

#ifndef SERIAL_H_
#define SERIAL_H_

//Initialize the module
void serial_init(void);

//Write a single byte
void serial_tx_byte(unsigned char data);

//Write a buffer to the UART
void serial_tx_buffer(unsigned char *buffer, unsigned int count);

//Check to see if data is available in the RX buffer
unsigned int serial_count_data_available(void);

//Read a byte from the RX buffer
unsigned char serial_read_byte(void);

//Read multiple bytes from the RX buffer
void serial_read_buffer(unsigned char buffer[], unsigned int count);

#endif /* SERIAL_H_ */
