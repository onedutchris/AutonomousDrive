/*
 * driver.h
 *
 *  Created on: Oct 18, 2014
 *      Author: cameronfranz
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#include "localizer.h"

struct waypoint {
	int x;
	int y;
	float heading;
	int liftHeight;
	int clawState;
};

void driver(void * ignore);
float calculateRotation(struct Particle * currentLocation, struct waypoint * goalLocation);
void setRotation(float rotationNeeded, int speed);
void setMovement(int speed);
void setDriveMotors(int leftMotor, int rightMotor);
int checkComlpeted(struct waypoint * waypoint);

#endif /* DRIVER_H_ */
