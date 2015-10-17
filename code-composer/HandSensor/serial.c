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

}

void serial_send_byte(unsigned char data) {
	//Check to see if waiting on transmit
	while(!(UCA0TXIFG&UCA0TXIFG)); //Busy loop while unable to TX.  TODO: Fix to be interrupt-based
	//Place data in transmit register
	UCA0TXBUF = data;
}
