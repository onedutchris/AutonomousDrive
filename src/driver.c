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

#define ROTATION_LEEWAY 0.2f
#define LOCATION_LEEWAY 3
#define LIFT_HEIGHT_LEEWAY 10

#define TURN_SPEED 30
#define FORWARD_SPEED 50

struct waypoint waypoints[] = {

{ .x = 0, .y = 1000, .rotation = 6.28f }

};
int currentWaypoint = 0;

void driver(void*ignore) {
	//printf("Driver Task Started \n");
	struct Particle location = Localizer_getWeightedAverage();
	float rotationNeeded = calculateRotation(&location, &waypoints[currentWaypoint]);

	printf("Rotation Needed : %f \n",rotationNeeded);

	//set all motors to 0
	setRotation(0,0);
	setMovement(0);

	if (fabsf(rotationNeeded) > ROTATION_LEEWAY) {
		setRotation(rotationNeeded, TURN_SPEED);
	}
	else if (abs(location.x - waypoints[currentWaypoint].x) > LOCATION_LEEWAY) {
		setMovement(FORWARD_SPEED);
	}

	if (abs(getLiftHeight() - waypoints[currentWaypoint].liftHeight) > LIFT_HEIGHT_LEEWAY) {

	}
	else if(abs(getClawState - waypoints[currentWaypoint].clawState)) {

	}

	//checkComlpeted(&waypoints[currentTask]);
	delay(50);
}

float calculateRotation(struct Particle * currentLocation,
		struct waypoint * goalLocation) {
	int dY = goalLocation->y - currentLocation->y;
	int dX = goalLocation->x - currentLocation->x;
	return (PI / 2 - atan2(dY, dX) - currentLocation->heading);
}

void setMovement(int speed) {
	setMotors(speed, speed);
}
void setRotation(float rotationNeeded, int speed) {
	if (rotationNeeded < 0) {
		setMotors(-speed, speed);
	} else {
		setMotors(speed, -speed);
	}
}

void setMotors(int leftSide, int rightSide) {
//TODO: PID Control
	motorSet(LEFT_MOTOR_1_PORT, leftSide);
	motorSet(LEFT_MOTOR_2_PORT, -leftSide);

	motorSet(RIGHT_MOTOR_1_PORT, rightSide);
	motorSet(RIGHT_MOTOR_2_PORT, -rightSide);

}

int getLiftHeight() {

}

int getClawState() {

}

