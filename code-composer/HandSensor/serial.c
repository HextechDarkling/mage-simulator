/*
 * serial.c
 *
 *  Created on: Oct 6, 2015
 *      Author: Alex
 */
#include <msp430.h>

#include "serial.h"

struct ringBuffer{
	unsigned char buffer[32];
	unsigned char head;
	unsigned char tail;
};

struct ringBuffer RXBuf;
struct ringBuffer TXBuf;

inline unsigned char count(struct ringBuffer* buffer) {
	return (buffer->tail - buffer->head) % 32;
}

inline unsigned char readByte(struct ringBuffer* buffer) {
	if(count(buffer) > 0) {
		unsigned char data;
		data = buffer->buffer[buffer->head];
		buffer->head += 1;
		buffer->head %= 32;
		return data;
	}
	return 0;
}

inline void writeByte(struct ringBuffer* buffer, unsigned char data) {
	if(count(buffer) < 32) {
		buffer->buffer[buffer->tail] = data;
		buffer->tail += 1;
		buffer->tail %= 32;
	}
}

void serial_init(void) {
	//Initialize GPIO to USCI function
	//Select RXD and TXD functions for Port 1
	P1SEL |= BIT1 + BIT2;
	P1SEL2 |= BIT1 + BIT2;

	//Source USCI module from SMCLK
	UCA0CTL1 |= UCSSEL_2;
	// (UCAxBR0 + UCAxBR1 × 256)
	UCA0BR0 = 0xE2;
	UCA0BR1 = 0x04;

	//Initialize state machine
	UCA0CTL1 &= ~UCSWRST;
	//Set internal variables to inital state
	RXBuf.head = 0;
	RXBuf.tail = 0;

	TXBuf.head = 0;
	TXBuf.tail = 0;

	//Enable interrupts for receive
	IE2 |= UCA0RXIE;
}

void serial_tx_byte(unsigned char data) {
	//Write byte to buffer
	writeByte(&TXBuf, data);
	//Start data transmission
	IE2 |= UCA0TXIE;
}

void serial_tx_buffer(unsigned char buffer[], unsigned int count) {
	int i;
	for(i = 0; i < count; i++) {
		writeByte(&TXBuf, buffer[i]);
	}
	//Start data transmission
	IE2 |= UCA0TXIE;
}

unsigned int serial_count_data_available(void) {
	return count(&RXBuf);
}

unsigned char serial_read_byte(void) {
	if(count(&RXBuf) > 0) {
		return readByte(&RXBuf);
	} else {
		return 0;
	}
}

void serial_read_buffer(unsigned char buffer[], unsigned int count) {
	int i;
	for(i = 0; i < count; i++) {
		buffer[i] = readByte(&RXBuf);
	}
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void) {
	//Transmitted a byte, load a new one
	UCA0TXBUF = readByte(&TXBuf);
	//Check to see if buffer is empty
	//Disable tx interrupt if so
	if(count(&TXBuf) == 0) {IE2 &= ~UCA0TXIE;}
	LPM3_EXIT;
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void) {
	//Received a byte, process it
	//Place data in receive buffer
	writeByte(&RXBuf, UCA0RXBUF);
	LPM3_EXIT;
}
