/*
 * Robot.h
 *
 *  Created on: Sep 25, 2014
 *      Author: cameronfranz
 */

#ifndef ROBOT_H_
#define ROBOT_H_

struct Robot Robot_move(struct Robot robot, int speed, int direction, int turnAngle); //convolute particles

float Robot_measurementProbability(struct Robot robot); //get measurement probability of particle

void Robot_setNoise(struct Robot * robot, float sonar_noise, float move_noise, float gyro_noise);

void Robot_init(struct Robot* robot, int mapSize);

#endif /* ROBOT_H_ */
