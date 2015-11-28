#include <msp430.h> 
#include <stdbool.h>

#include "serial.h"
#include "i2c.h"

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

    __bis_SR_register(GIE);

    i2c_set_slave_address(0x68);

    unsigned char results[12];

    while(1) {
    	//Read X Acceleration
    	i2c_start(true);
		i2c_tx_byte(0x3B);
		i2c_start(false);
		results[0] = i2c_rx_byte() * 256;
		i2c_stop();

		i2c_start(true);
		i2c_tx_byte(0x75);//0x3C);
		i2c_start(false);
		results[1] = i2c_rx_byte();
		i2c_stop();

		//Read Y Acceleration
		i2c_start(true);
		i2c_tx_byte(0x3D);
		i2c_start(false);
		results[2] = i2c_rx_byte() * 256;
		i2c_stop();

		i2c_start(true);
		i2c_tx_byte(0x3E);
		i2c_start(false);
		results[3] = i2c_rx_byte();
		i2c_stop();

		//Read Z Acceleration
		i2c_start(true);
		i2c_tx_byte(0x3F);
		i2c_start(false);
		results[4] = i2c_rx_byte() * 256;
		i2c_stop();

		i2c_start(true);
		i2c_tx_byte(0x40);
		i2c_start(false);
		results[5] = i2c_rx_byte();
		i2c_stop();

		//Read X Angular Acceleration
		i2c_start(true);
		i2c_tx_byte(0x43);
		i2c_start(false);
		results[6] = i2c_rx_byte() * 256;
		i2c_stop();

		i2c_start(true);
		i2c_tx_byte(0x44);
		i2c_start(false);
		results[7] = i2c_rx_byte();
		i2c_stop();

		//Read Y Angular Acceleration
		i2c_start(true);
		i2c_tx_byte(0x45);
		i2c_start(false);
		results[8] = i2c_rx_byte() * 256;
		i2c_stop();

		i2c_start(true);
		i2c_tx_byte(0x46);
		i2c_start(false);
		results[9] = i2c_rx_byte();
		i2c_stop();

		//Read Z Angular Acceleration
		i2c_start(true);
		i2c_tx_byte(0x47);
		i2c_start(false);
		results[10] = i2c_rx_byte() * 256;
		i2c_stop();

		i2c_start(true);
		i2c_tx_byte(0x48);
		i2c_start(false);
		results[11] = i2c_rx_byte();
		i2c_stop();

		serial_tx_buffer(results, 12);
		__delay_cycles(1000000);
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
