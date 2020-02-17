/*
 * AttitudeLibrary.h
 *
 *  Created on: 8 feb. 2020
 *      Author: leandro
 */

#ifndef ATTITUDELIBRARY_H_
#define ATTITUDELIBRARY_H_


/**********************************************************
 * Definitions
 *********************************************************/
#define Kp	1.0
#define Ki	0.0
#define Kd	0.0


/*********************************************************************************************
 * @brief Proportional controller
 *
 * @param reference angle
 *
 * @return controller output
 *********************************************************************************************/
float PID_controller(float ref);



#endif /* ATTITUDELIBRARY_H_ */
