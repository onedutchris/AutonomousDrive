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
	float gyro;
};
#define PI 3.14

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
#define MOVE_PER_TICK 0.03757f // (18/24 * 10 * PI) / 627.1
#define ROBOT_WIDTH 10.0f

//map data - no grid map because that's too large
#define NUM_LINES 8
#define NUM_CUBES 10
const struct cube cubes[NUM_CUBES];
const struct line lines[NUM_LINES];
#define MAP_SIZE 100
const struct Particle start_position = {.x = 0, .y = 0, .heading = 0};

//Particles
#define NUM_PARTICLES 100
struct Particle particles[NUM_PARTICLES];
struct SensorData sensorValues;
float moveDistance;
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
		initialize_particle(&particles[i], &start_position);
	}

}

void localizer(void* ignore) {
	printf("Started Localizer Task");
	initialize_filter();

	//delay to allow calibrations
	delay(2000);
	imeReset(LEFT_MOTOR_IME);
	imeReset(RIGHT_MOTOR_IME);
	while (1) {
		sensorValues = sense();
		moveDistance = calculateMovement(sensorValues.leftEncoder,sensorValues.rightEncoder);
		update_filter(moveDistance, sensorValues.gyro);

		//printf("Encoder: %d, %d \n", sensorValues.leftEncoder, sensorValues.rightEncoder);
		//printf("Movement Forward: %f \n",moveDistance);
		//printf("Gyro: %f \n", sensorValues.gyro);
		//printf("Particle1: X is %d, Y is %d, Theta is %f \n", particles[1].x,particles[1].y,particles[1].heading);
		//printf("Particle2: X is %d, Y is %d, Theta is %f \n\n", particles[2].x,particles[2].y,particles[2].heading);
		struct Particle avg = getWeightedAverage();
		printf("Weighted Average: X is %d, Y is %d, Theta is %f \n",avg.x,avg.y,avg.heading);
		delay(500);
	}
}

void update_filter(float distance, float rotation) {

	//move Particles
	for (int i = 0; i< NUM_PARTICLES; i++) {
		move_particle(&particles[i], distance, rotation);
	}

	//update the weights
	//weights = mes_prob_particles(Particles);

	//resample Particles
	//Particles = resample_particles(Particles);
}

struct SensorData sense() {
	struct SensorData values;
	imeGet(LEFT_MOTOR_IME, &values.leftEncoder);
	imeGet(RIGHT_MOTOR_IME, &values.rightEncoder);
	values.gyro = gyroGet(gyro) * 0.01745f;
	values.leftSonar = ultrasonicGet(leftSonar);
	values.rightSonar = ultrasonicGet(rightSonar);

	imeReset(LEFT_MOTOR_IME);
	imeReset(RIGHT_MOTOR_IME);
	gyroReset(gyro);
	return values;

}

//*****PARTICLE FILTER METHODS******//

void initialize_particle(struct Particle * particle, struct Particle * startPos) {
	particle->x = startPos->x;
	particle->y = startPos->y;
	particle->heading = startPos->heading;
	particle->weight = 1.0f/NUM_PARTICLES;
}

//simplified motion model assuming robot turns then moves
void move_particle(struct Particle * particle, float distance, float direction) {
	distance += gaussianNoise(0,distance/5);
	float newHeading = particle->heading + direction + gaussianNoise(0,direction/5);
	particle->x += sin(newHeading) * distance;
	particle->y += cos(newHeading) * distance;
	particle->heading = fmodf(newHeading, (2 * PI)); //keep within -2pi to 2pi
	//printf("direction: %f, oldParticleHeading: newHeading: %f",direction,newHeading,particle->heading);

}

void mes_prob_particle(struct Particle * particle) {

}

float calculateMovement(int leftEncoderValue, int rightEncoderValue) {
	//TODO: more accurate movement model
	//struct Particle translation;
	float SL = -leftEncoderValue * MOVE_PER_TICK;
	float SR = rightEncoderValue * MOVE_PER_TICK;
	float meanS = (SL + SR) / 2;
	return meanS;
	//float theta = (SL - SR) / ROBOT_WIDTH;
	//translation.heading = theta;
	//translation.x = meanS * cos(theta);
	//translation.y = meanS * sin(theta);
	//return translation;
	//distance = (left_encoder + right_encoder) / 2.0
	//(2)	theta = (left_encoder - right_encoder) / WHEEL_BASE;
}

float gaussianNoise (int mu, int sigma) {
	//taken from wikiipedia
	//TODO: more efficient polar method
	static int haveSpareRandoms = 0;
	static double rand1, rand2;

	//use the other equation of box muller transformation
	if(haveSpareRandoms) {
		haveSpareRandoms = 0;
		return (sqrt(rand1) * sin(rand2) * sigma) + mu;
	}
	haveSpareRandoms = 1;
	rand1 = rand() / (double) RAND_MAX;
	//printf("RAND1: %f \n", rand1);
	//if(rand1 < 1e-6) rand1 = 1e-6;
	rand1 = -2 * log(rand1);
	//printf("Log RAND1: %f \n", rand1);
	rand2 = (rand() / ((double) RAND_MAX)) * 2 * PI;

	return (sqrt(rand1) * cos(rand2) * sigma) + mu;
}

struct Particle getWeightedAverage(){
	struct Particle average;
	float avgX=0;
	float avgY=0;
	float avgT=0;
	for (int i = 0; i < NUM_PARTICLES; i++) {
		float weight = particles[i].weight;
		avgX += particles[i].x*weight;
		avgY += particles[i].y*weight;
		avgT += particles[i].heading*weight;
	}
	average.x = (int)avgX;
	average.y = (int)avgY;
	average.heading = avgT;

	return average;
}

#endif /* LOCALIZER_C_ */
