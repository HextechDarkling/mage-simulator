#include <msp430.h> 
#include <stdbool.h>

#include "serial.h"
#include "i2c.h"
#include "sensor.h"

/*
 * main.c
 */

//Prototypes
void clock_init(void);
void gpio_init(void);

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    clock_init();
    gpio_init();
    serial_init();
    i2c_init();
    //sensor_init();

    __bis_SR_register(GIE);

    int results[6];

    while(true) {
        //sensor_read(false, results);
    	i2c_set_slave_address(0x86);
		i2c_start(true);	//Gyro Init
		i2c_tx_byte(0x1B);
		i2c_tx_byte(0x08);
		i2c_stop();
    }

	return 0;
}

void clock_init(void) {
	//Init DCO to 12MHz calibrated
	DCOCTL = CALDCO_12MHZ;
	BCSCTL1 = CALBC1_12MHZ;

	//Init MCLK to 12MHz DCO
	//Init SMCLK to 12MHz DCO
	//BCSCTL2 remains default

	//BCSCTL3 remains default
}

void gpio_init(void) {
	//Initialize GPIO to Output and low signal to prevent floating inputs
	//Settings for Serial IO and such will be handled by the peripheral drivers
	P1DIR = 0xFF;
	P1OUT = 0x00;

	P2DIR = 0xFF;
	P2OUT = 0x00;

	P3DIR = 0xFF;
	P3OUT = 0x00;

}
