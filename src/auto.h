/*
 * auto.h
 *
 *  Created on: Sep 8, 2014
 *      Author: cameronfranz
 */

#ifndef AUTO_H_
#define AUTO_H_

//turn, direction in degrees
void turn(int speed, int direction);

//get data from environment
void sense();

//convolute functions
void update();

//move robot
void move();

void setMotors();

#endif /* AUTO_H_ */
