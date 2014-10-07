/*
 * auto.h
 *
 *  Created on: Sep 8, 2014
 *      Author: cameronfranz
 */

#ifndef AUTO_H_
#define AUTO_H_

void sense();
void update_filter();
void move(int speed, int direction, int turnAngle);
void setMotors();
void calculateMovement();
struct Particle * init_particles();
struct Particle * move_particles(struct Particle Particle, int speed, int direction, int turnAngle); //convolute Particles
float mes_prob_particles(struct Particle Particle); //get measurement probability of Particle
void set_noise_particles(struct Particle * Particle, float sonar_noise, float move_noise, float gyro_noise);
void Auto_init();

#endif /* AUTO_H_ */
