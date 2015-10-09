/*
 * serial.c
 *
 *  Created on: Oct 6, 2015
 *      Author: Alex
 */
#include <msp430.h>

#include "serial.h"

void serial_init(void) {
	//Initialize GPIO to USCI function
	//Select RXD and TXD functions for Port 1
	P1SEL0 |= 0x05;
	P1SEL1 |= 0x05;

	//Source USCI module from SMCLK
	UCA0CTL1 |= UCSSEL_2;
	//UCBRx = 625, UCBRSx = 0, UCBRFx = 0, 19200 baud
	UCA0BR0 = 113;
	UCA0BR1 = 2;

	//Set internal variables to inital state

}

void serial_send_byte(unsigned char data) {
	//Check to see if waiting on transmit

	//Place data in transmit register
}
