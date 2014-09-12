/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "shared.h"
#include "auto.h"

extern Ultrasonic leftSonar;
extern Ultrasonic rightSonar;
extern Gyro gyro;

int TURN_DISTANCE = 35;
int BACKUP_DISTANCE = 10;

int leftSonarValue;
int rightSonarValue;

int leftMotorValue;
int rightMotorValue;

typedef enum {
	SEARCHING, DEPOSITING
} STATE;

STATE currentState;
/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

void autonomous() {
	leftMotorValue = 0;
	rightMotorValue = 0;

	sense();
	update();
}

void turn(int speed, int direction) {
	leftMotorValue =  direction * speed;
	rightMotorValue =  direction * speed;
}

void move(int speed, int direction) {
	leftMotorValue =  direction * speed;
	rightMotorValue =  -direction * speed;
}

void update() {
	if (leftSonarValue > rightSonarValue) {
		if (rightSonarValue != 0) {
			if (rightSonarValue <= BACKUP_DISTANCE) {
				move(50, -1);
			} else if (rightSonarValue <= TURN_DISTANCE) {
				turn(50, -1);
			} else {
				move(50, 1);
			}
		} else {
			move(50, 1);
		}
	} else if (leftSonarValue < rightSonarValue) {
		if (leftSonarValue != 0) {
			if (leftSonarValue <= BACKUP_DISTANCE) {
				move(50, -1);
			} else if (leftSonarValue <= TURN_DISTANCE) {
				turn(50, 1);
			} else {
				move(50, 1);
			}
		} else {
			move(50, 1);
		}

	}
	setMotors();
}

void sense() {
	leftSonarValue = ultrasonicGet(leftSonar);
	rightSonarValue = ultrasonicGet(rightSonar);
}

void setMotors() {
	motorSet(LEFT_MOTOR_PORT, leftMotorValue);
	motorSet(RIGHT_MOTOR_PORT, rightMotorValue);
}

