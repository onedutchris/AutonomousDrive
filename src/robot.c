/*
 * robot.c
 *
 *  Created on: Sep 25, 2014
 *      Author: cameronfranz
 */
#include <time.h>
#include <stdlib.h>
#include <auto.h>


void Robot_init(struct Robot * robot, int mapSize) {
	srand(time(NULL));
	robot->x = (int) rand()*mapSize;
	robot->y = (int) rand()*mapSize;
	robot->heading = rand() * 2 * 3.14;
}

struct Robot Robot_move(struct Robot robot, int speed, int direction, int turnAngle) {


}

float Robot_measurementProbability(struct Robot robot) {

}
void Robot_setNoise(struct Robot * robot, float sonar_noise, float move_noise,float gyro_noise) {

};





