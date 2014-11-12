/*
 * Localizer.h
 *
 *  Created on: Oct 10, 2014
 *      Author: cameronfranz
 */

#ifndef LOCALIZER_H_
#define LOCALIZER_H_

struct Particle {
	int x;
	int y;
	float heading;
	float weight;
};

//private
struct SensorData sense();
void update_filter(float distance,float rotation);
float calculateMovement(int leftEncoder, int rightEncoder);
struct Particle * init_particles();

float gaussianNoise(int mu, int sigma);
void initialize_filter();
void initialize_particle(struct Particle * particle, struct Particle * startPos);
void move_particle(struct Particle * particle, float distance, float direction); //convolute Particles
void mes_prob_particle(struct Particle * particle); //get measurement probability of Particle
void localizer(void * ignore);

//public
struct Particle Localizer_getWeightedAverage();
int Localizer_getLiftHeight();
int Localizer_getClawState();

#endif /* LOCALIZER_H_ */
