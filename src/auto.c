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
 * Purdue Particleics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */
/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the Particle is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the Particle is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the Particle will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the Particle will await a switch to another mode or disable/enable cycle.
 */
#include "main.h"
#include "shared.h"
#include "auto.h"
#include <Math.h>

//custom data types
struct cube {
	int xPos;
	int yPos;
};
struct line {
	int slope;
	int yIntercept;
	bool isWall; //tape or wall
};
typedef enum {
	SEARCHING, DEPOSITING
} STATE;

struct Particle {
	int x;
	int y;
	float heading;
	float weight;
};


//external sensors
extern Ultrasonic leftSonar;
extern Ultrasonic rightSonar;
extern Gyro gyro;

STATE currentState;

//sensor cosntants
#define ULTRASONIC_NOISE 0.5
#define ENCODER_NOISE 0.5
#define LINE_TRACKER_NOISE 0.5
#define POTENTIOMETER_NOISE 0.5

//movement constants
#define WHEEL_RADIUS

//map data - no grid map because that's too large
#define NUM_LINES 8
#define NUM_CUBES 10
const struct cube cubes[NUM_CUBES];
const struct line lines[NUM_LINES];
#define MAP_SIZE 100

//Particles
#define NUM_PARTICLES 100
struct Particle * particles;

/*//sensor and motor data
int leftSonarValue;
int rightSonarValue;

int leftMotorValue;
int rightMotorValue;
*/

//filter parameters


//implementations
void Auto_init() {
	//initialize Particles
	particles = init_particles();
}

void autonomous() {

	//update movement values
	//calculateMovement();

	//move();
	//update sensor values
	sense();

	//update_filter();
}

void move(int speed, int direction, int turnAngle) {
	int turnMagnitude = -((abs(turnAngle)-45)/45);
	if (turnAngle > 0) {
//		leftMotorValue  = (int)(direction * speed);
//		rightMotorValue = (int)(direction * speed * turnMagnitude);
	}
	else if (turnAngle <= 0){
//		leftMotorValue  = (int)(direction * speed * turnMagnitude);
//		rightMotorValue = (int)(direction * speed);
	}
}

void update_filter() {

	//update the weights
	//weights = mes_prob_particles(Particles);

	//move Particles
	//Particles = convolute_particles(Particles);

	//resample Particles
	//Particles = resample_particles(Particles);

	setMotors();
}

void sense() {
	//leftSonarValue = ultrasonicGet(leftSonar);
	//rightSonarValue = ultrasonicGet(rightSonar);

	//if (leftSonarValue == 0) {
		//leftSonarValue = 300;
	//}
	//if (rightSonarValue == 0) {
	//		rightSonarValue = 300;
		}
}

void setMotors() {
	//motorSet(LEFT_MOTOR_1_PORT, leftMotorValue);
	//motorSet(LEFT_MOTOR_2_PORT, leftMotorValue);
	//motorSet(RIGHT_MOTOR_1_PORT, -rightMotorValue);
	//motorSet(RIGHT_MOTOR_2_PORT, -rightMotorValue);
}

//*****PARTICLE FILTER METHODS******//

struct Particle * init_particles() {
	struct Particle p[NUM_PARTICLES];
	for (int i = 0; i<NUM_PARTICLES; i++) {
			p[i].x = (int) floor(((float)rand()/RAND_MAX)*MAP_SIZE);
			p[i].y = (int) floor(((float)rand()/RAND_MAX)*MAP_SIZE);
			p[i].heading = ((float)rand()/RAND_MAX) * 2 * 3.14;
	}
	return p;
}

//TODO: Fix motion model
struct Particle * move_particles(struct Particle p[], int speed, int direction, int turnAngle) {

}

float mes_prob_particles(struct Particle Particle) {

}
void Particle_setNoise(struct Particle * Particle, float sonar_noise, float move_noise,float gyro_noise) {

};
