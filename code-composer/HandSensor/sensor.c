/*
 * sensor.c
 *
 *  Created on: Nov 28, 2015
 *      Author: hexte
 */

#include <msp430.h>
#include "sensor.h"
#include "i2c.h"

void sensor_init() {
	//Init left hand sensor
	i2c_set_slave_address(ADDRESS_LEFT);
	i2c_start(true);	//Gyro Init
	i2c_tx_byte(0x1B);
	i2c_tx_byte(0x08);
	i2c_stop();

	i2c_start(true);	//Accel Init
	i2c_tx_byte(0x1C);
	i2c_tx_byte(0x08);
	i2c_stop();

}

void sensor_read(bool rightHand, int buffer[]) {
	if(rightHand) {
		i2c_set_slave_address(ADDRESS_RIGHT);
	} /*else {
		i2c_set_slave_address(ADDRESS_LEFT);
	}*/

	i2c_start(true);
	i2c_tx_byte(0x3B);
	i2c_start(false);
	buffer[0] = i2c_rx_byte() * 256;	//X Accel
	buffer[0] = i2c_rx_byte();
	buffer[1] = i2c_rx_byte() * 256;	//Y Accel
	buffer[1] = i2c_rx_byte();
	buffer[2] = i2c_rx_byte() * 256;	//Z Accel
	buffer[2] = i2c_rx_byte();

	buffer[3] = i2c_rx_byte() * 256;	//X Gyro
	buffer[3] = i2c_rx_byte();
	buffer[4] = i2c_rx_byte() * 256;	//Y Gyro
	buffer[4] = i2c_rx_byte();
	buffer[5] = i2c_rx_byte() * 256;	//Z Gyro
	buffer[5] = i2c_rx_byte();
	i2c_stop();

}
