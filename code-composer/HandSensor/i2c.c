/*
 * i2c.c
 *
 *  Created on: Nov 12, 2015
 *      Author: Alex
 */

#include "i2c.h"

/* The recommended USCI initialization or reconfiguration process is:
1. Set UCSWRST (BIS.B #UCSWRST,&UCxCTL1)
2. Initialize all USCI registers with UCSWRST=1 (including UCxCTL1)
3. Configure ports.
4. Clear UCSWRST via software (BIC.B #UCSWRST,&UCxCTL1)
5. Enable interrupts (optional) via UCxRXIE and/or UCxTXIE */

void i2c_init(void) {
	//Init all USCI registers
	UCB0CTL0 |= UCMST + UCMODE_3 + UCSYNC;	//I2C mode, Master mode
	UCB0CTL1 |= UCSSEL_2;	//Source from 12MHz SMCLK

	//Prescaler of 120 for 100kHz clock speed
	UCB0BR0 = 120;
	UCB0BR1 = 0;

	//Confugre port functions
	P1SEL |= BIT6 + BIT7;
	P1SEL2 |= BIT6 + BIT7;

	//Start module
	UCB0CTL1 &= ~UCSWRST;
}

