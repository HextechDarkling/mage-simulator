/*
 * sensor.h
 *
 *  Created on: Nov 28, 2015
 *      Author: hexte
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include <stdbool.h>

#define ADDRESS_LEFT	0x68	//LSB 0
#define ADDRESS_RIGHT	0x69	//LSB 1

//Initialize the sensor
//MUST INIT I2C BEFORE THIS
void sensor_init();

//Return sensor values.
//Order is: ACC_X, ACC_Y, ACC_Z, GYR_X, GYR_Y, GYR_Z
//Buffer must be at least 6 values wide
void sensor_read(bool rightHand, int buffer[]);



#endif /* SENSOR_H_ */
