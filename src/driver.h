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
	float rotation;
	int liftHeight;
	int completed;
};

void driver(void * ignore);
float calculateRotation(struct Particle * currentLocation, struct waypoint * goalLocation);

#endif /* DRIVER_H_ */
