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

#define ROTATION_LEEWAY 0.5f

struct waypoint waypoints[] = {

{ .x = 0, .y = 100, .rotation = 6.28f }

};
int currentTask = 0;

void driver(void*ignore) {
	struct Particle location = getWeightedAverage();
	float rotationNeeded = calculateRotation(&location,
			&waypoints[currentTask]);
	if (fabsf(rotationNeeded) > ROTATION_LEEWAY) {
		setRotation(rotationNeeded);
	} else {
		setMovement();
	}
	//checkComlpeted(&waypoints[currentTask]);
	delay(20);
}

float calculateRotation(struct Particle * currentLocation,
		struct waypoint * goalLocation) {
	int dY = goalLocation->y - currentLocation->y;
	int dX = goalLocation->x - currentLocation->x;
	return (PI / 2 - atan2(dY, dX)) + currentLocation->heading;
}

void setMovement() {
	setMotors(50, 50);
}
void setRotation(float rotationNeeded) {
	printf("Required Rotation: %f \n", rotationNeeded);
	if (rotationNeeded < 0) {
		setMotors(-50, 50);
	} else {
		setMotors(50, -50);
	}
}

void setMotors(int leftSide, int rightSide) {
//TODO: PID Control
	motorSet(LEFT_MOTOR_1_PORT, leftSide);
	motorSet(LEFT_MOTOR_2_PORT, -leftSide);

	motorSet(RIGHT_MOTOR_1_PORT, rightSide);
	motorSet(RIGHT_MOTOR_2_PORT, -rightSide);

}

