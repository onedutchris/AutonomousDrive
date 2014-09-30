/*
 * robot.c
 *
 *  Created on: Sep 25, 2014
 *      Author: cameronfranz
 */
#include <stdlib.h>
#include <auto.h>
#include "main.h"
#include <time.h>
#include<math.h>

void Robot_init(struct Robot * robot, int mapSize) {
	//TODO: random seed
	//srand(time(NULL));
	robot->x = (int) floor(((float)rand()/RAND_MAX)*mapSize);
	robot->y = (int) floor(((float)rand()/RAND_MAX)*mapSize);
	robot->heading = ((float)rand()/RAND_MAX) * 2 * 3.14;
}

struct Robot Robot_move(struct Robot robot, int speed, int direction, int turnAngle) {


}

float Robot_measurementProbability(struct Robot robot) {

}
void Robot_setNoise(struct Robot * robot, float sonar_noise, float move_noise,float gyro_noise) {

};





