/*
 * motor.h
 *
 *  Created on: Feb 2, 2023
 *      Author: vienchau
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include <stdint.h>
#include "tim.h"
#include "gpio.h"
#include "pid.h"


#define MOTOR_1 1
#define MOTOR_2 2
//#define TotalPulse 7500
//#define TotalDeg 360
#define PPR 11880
#define PTD 360 / 11880;


#define HEAD 1
#define BACK 0

typedef struct
{
	uint16_t counter;
	float velocity;
	float position;
    float setPoint;
    float p_ref;
    float v_ref;
} Motor_t;


typedef struct
{
    float dAccelMax;
    float dVelMax;
    float dPosMax;
    float dA1;
    float dA2, dB2;
    float dA3, dB3, dC3;
    float dMidStep1;
    float dMidStep2;
    float dMidStep3;
    float nTime;
//    uint8_t Direct;
} PROFILE_t;

enum
{
    NONE = 0,
    RUN_TEST
};

extern PROFILE_t tProfile;
extern Motor_t tMotor1, tMotor2;

extern void MotorTrapzoidalInit(PROFILE_t *tProfile, float maxPos, float maxVel, float maxAcc);
extern void MotorSetRun();
extern void Motor1Forward();
extern void Motor1Backward();
extern void Motor2Forward();
extern void Motor2Backward();
extern void Motor2Backward();
extern void ReadEncoder(Motor_t *tmotor, TIM_HandleTypeDef *htim);
extern void MotorInit(void);
#endif /* INC_MOTOR_H_ */
