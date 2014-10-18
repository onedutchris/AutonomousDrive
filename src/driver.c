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


struct waypoint testPoint = {.x = 0, .y = 100, .rotation = 6.28f};

void driver (void*ignore) {
	delay(2000);
	struct Particle location = getWeightedAverage();
	printf("rotation %f \n",calculateRotation(&location,&testPoint));
}

float calculateRotation(struct Particle * currentLocation, struct waypoint * goalLocation) {
	int dY = goalLocation->y - currentLocation->y;
	int dX = goalLocation->x - currentLocation->x;
	return PI/2-atan2(dY, dX);
}

