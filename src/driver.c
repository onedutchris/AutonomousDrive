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
#define LIFT_SPEED 128
#define PI 3.14

struct waypoint waypoints[] = {

		{ .x = 0, .y = 1000, .rotation = 6.28f}
};
int currentWaypoint = 0;

void driver(void*ignore) {
	printf("Driver Task Started \n");

	//change routine based upons start position
	/*switch(ROBOT_START_POS) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
*/
	while(1) {

		if(!isAutonomous()){
			taskDelete(NULL); //exit this task if not in autonomous
		}

	struct Particle location = Localizer_getWeightedAverage();
	float rotationNeeded = calculateRotation(&location, &waypoints[currentWaypoint]);
	//printf("Rotation Needed : %f \n",rotationNeeded);

	//set all motors to 0
	setRotation(0,0);
	setMovement(0);

	bool completed = true;

	if (fabsf(rotationNeeded) > ROTATION_LEEWAY) {
		setRotation(rotationNeeded, TURN_SPEED);
		completed = false;
	}
	else if (abs(location.x - waypoints[currentWaypoint].x) > LOCATION_LEEWAY) {
		setMovement(FORWARD_SPEED);
		completed = false;
	}

	if (abs(Localizer_getLiftHeight() - waypoints[currentWaypoint].liftHeight) > LIFT_HEIGHT_LEEWAY) {
		//setLift(LIFT_SPEED);
		completed = false;
	}
	else {
		setClaw(waypoints[currentWaypoint].liftHeight);
	}

	if (completed) {
		currentWaypoint++;
	}
	delay(50); }
}

float calculateRotation(struct Particle * currentLocation, struct waypoint * goalLocation) {
	int dY = goalLocation->y - currentLocation->y;
	int dX = goalLocation->x - currentLocation->x;
	return (PI / 2 - atan2(dY, dX) - currentLocation->heading);
}

void setLift(int speed) {
	motorSet(LEFT_LIFT_MOTOR_1_PORT,  1 * speed);
	motorSet(LEFT_LIFT_MOTOR_2_PORT, -1 * speed);
	motorSet(LEFT_LIFT_MOTOR_3_PORT,  1 * speed);
	motorSet(RIGHT_LIFT_MOTOR_1_PORT,-1 * speed);
	motorSet(RIGHT_LIFT_MOTOR_2_PORT, 1 * speed);
	motorSet(RIGHT_LIFT_MOTOR_3_PORT,-1 * speed);
}

void setClaw(int state) {
	//opened
	if (state == 1) {
		digitalWrite(CLAW_SOL_PIN,HIGH);
	}
	//closed
	if (state==0) {
		digitalWrite(CLAW_SOL_PIN,LOW);
	}
}

void setMovement(int speed) {
	setDriveMotors(speed, speed);
}
void setRotation(float rotationNeeded, int speed) {
	if (rotationNeeded < 0) {
		setDriveMotors(-speed, speed);
	} else {
		setDriveMotors(speed, -speed);
	}
}

void setDriveMotors(int leftSide, int rightSide) {
//TODO: PID Control
	motorSet(LEFT_MOTOR_1_PORT, leftSide);
	motorSet(LEFT_MOTOR_2_PORT, -leftSide);

	motorSet(RIGHT_MOTOR_1_PORT, rightSide);
	motorSet(RIGHT_MOTOR_2_PORT, -rightSide);
}
