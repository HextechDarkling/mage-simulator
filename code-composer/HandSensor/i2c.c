/*
 * I2C.c
 *
 *  Created on: Oct 16, 2015
 *      Author: Alex
 */

#include <msp430.h>

#include "i2c.h"

/* To transmit a byte:
 * Write slave address to UCB0I2CSA
 * Set UCSLA10 bit for 10 bit mode
 * Set UCTR for transmitter mode
 * Set UCTXSTT to generate START condition
 *
 * -- Generates START and transmits slave address
 *
 * Check UCB0TXIFG, will be set after transmit done
 * Write data to transmit to UCB0TXBUF
 *
 * -- Transmits data to slave
 *
 * Check UCB0TXIFG, will be set after transmit done
 * Set UCTXSTP to generate STOP condition
 *
 * -- Generates STOP
 */

void i2c_init(void) {
	/* The recommended USCI initialization or reconfiguration process is:
		1. Set UCSWRST (BIS.B #UCSWRST,&UCxCTL1)
		2. Initialize all USCI registers with UCSWRST=1 (including UCxCTL1)
		3. Configure ports.
		4. Clear UCSWRST via software (BIC.B #UCSWRST,&UCxCTL1)
		5. Enable interrupts (optional) via UCxRXIE and/or UCxTXIE
	*/

	UCB0CTL0 |= UCMST + UCMODE_3;	//I2C mode, Master
	UCB0CTL1 |= UCSSEL_2;			//SMCLK source @ 12MHz
	UCB0BR0 = 120;					//12MHz / 120 = 100kHz BRCLK

	P1SEL |= BIT6 + BIT7;
	P1SEL2 |= BIT6 + BIT7;


}

void i2c_tx_byte(unsigned int address, unsigned char data) {
	UCB0I2CSA = address;

}
