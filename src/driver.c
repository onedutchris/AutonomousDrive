/*
 * driver.c
 *
 *  Created on: Oct 18, 2014
 *      Author: cameronfranz
 */

#include "main.h"
#include "localizer.h"
#include <math.h>
#include "driver.h"
#include "shared.h"

#define ROTATION_LEEWAY 0.4f

struct waypoint waypoints[] = {

		{.x = 0, .y = 100, .rotation = 6.28f}


};
int currentTask = 0;

void driver (void*ignore) {
	delay(2000);
	struct Particle location = getWeightedAverage();
	float rotationNeeded = calculateRotation(&location,&waypoints[currentTask]);
	printf("rotation %f \n",calculateRotation(&location,&waypoints[currentTask]));
	setRotation(rotationNeeded);
	setMovement(&location,&waypoints[currentTask]);
	checkComlpeted(&waypoints[currentTask]);
}

float calculateRotation(struct Particle * currentLocation, struct waypoint * goalLocation) {
	int dY = goalLocation->y - currentLocation->y;
	int dX = goalLocation->x - currentLocation->x;
	return PI/2-atan2(dY, dX);
}

void setMovement(struct Particle * location,struct waypoint * waypoint) {}

