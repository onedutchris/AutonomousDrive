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


struct SensorData sense();
void update_filter();
struct Particle calculateMovement();
struct Particle * init_particles();

void initialize_particle(struct Particle * particle);
void move_particle(struct Particle * particle, struct Particle * translation); //convolute Particles
void mes_prob_particle(struct Particle * particle); //get measurement probability of Particle
void set_noise_particle(struct Particle * particle, float sonar_noise, float move_noise, float gyro_noise);

#endif /* LOCALIZER_H_ */
