/*
 * Localizer.c
 *
 *  Created on: Oct 10, 2014
 *      Author: cameronfranz
 */

#ifndef LOCALIZER_C_
#define LOCALIZER_C_

#include "main.h"
#include "shared.h"
#include <Math.h>
#include "Localizer.h"

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
struct SensorData {
	int leftEncoder;
	int rightEncoder;
	int leftSonar;
	int rightSonar;
	int lineTracker1;
	int lineTracker2;
	int lineTracker3;
};

//external sensors
extern Ultrasonic leftSonar;
extern Ultrasonic rightSonar;
extern Gyro gyro;

//sensor constants
#define ULTRASONIC_NOISE 0.5
#define ENCODER_NOISE 0.5
#define LINE_TRACKER_NOISE 0.5
#define POTENTIOMETER_NOISE 0.5

//movement constants
#define MOVE_PER_TICK 0.1f
#define ROBOT_WIDTH 10.0f

//map data - no grid map because that's too large
#define NUM_LINES 8
#define NUM_CUBES 10
const struct cube cubes[NUM_CUBES];
const struct line lines[NUM_LINES];
#define MAP_SIZE 100

//Particles
#define NUM_PARTICLES 100
struct Particle particles[NUM_PARTICLES];
struct SensorData sensorValues;
/*//sensor and motor data
 int leftSonarValue;
 int rightSonarValue;

 int leftMotorValue;
 int rightMotorValue;
 */

//filter parameters

//implementation
void initialize_filter() {
	//initialize particles
	for (int i = 0; i < NUM_PARTICLES; i++) {
		initialize_particle(&particles[i]);
	}

}

void particleFilter(void* ignore) {
	initialize_filter();
	struct Particle translation = calculateMovement(10,0);
	printf("Translation: %d %d %f", translation.x,translation.y,translation.heading);
	while (true) {
		sensorValues = sense();
		//calculateMovement;
		update_filter();
		wait(30);
	}
}

void update_filter() {

	//move Particles
	//Particles = convolute_particles(Particles);

	//update the weights
	//weights = mes_prob_particles(Particles);

	//resample Particles
	//Particles = resample_particles(Particles);
}

struct SensorData sense() {
	struct SensorData values;
	imeGet(LEFT_MOTOR_IME, &values.leftEncoder);
	imeGet(RIGHT_MOTOR_IME, &values.rightEncoder);
	return values;

}

//*****PARTICLE FILTER METHODS******//

void initialize_particle(struct Particle * particle) {
	particle->x = (int) floor(((float) rand() / RAND_MAX) * MAP_SIZE);
	particle->y = (int) floor(((float) rand() / RAND_MAX) * MAP_SIZE);
	particle->heading = ((float) rand() / RAND_MAX) * 2 * 3.14;
}

//TODO: Fix motion model
void move_particle(struct Particle * particle, struct Particle * translation) {
	particle->x += translation->x;
	particle->y += translation->y;
	particle->heading += fmodf(translation->heading, (2 * PI)); //normalize
}

void mes_prob_particle(struct Particle * particle) {

}

struct Particle calculateMovement(int leftEncoderValue, int rightEncoderValue) {
	//TODO: more accurate movement model
	struct Particle translation;
	float SL = leftEncoderValue * MOVE_PER_TICK;
	float SR = rightEncoderValue * MOVE_PER_TICK;
	float meanS = (SL + SR) / 2;
	float theta = (SL - SR) / ROBOT_WIDTH;
	translation.heading = theta;
	translation.x = meanS * cos(theta);
	translation.y = meanS * sin(theta);
	return translation;

}

#endif /* LOCALIZER_C_ */
