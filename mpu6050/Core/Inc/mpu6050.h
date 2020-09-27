/*
 * mpu6050.h
 *
 *  Created on: Sep 27, 2020
 *      Author: DELL
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "main.h"
#include "math.h"
#define MPU_6050_ADDRESS 0xD0
#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define INT_ENABLE_REG 0x38
#define USER_CONTROL_REG 0x6A
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define a 0.985
#define PI 3.14159265

void MPU6050_Init();
void MPU6050_Read_Data();
void MPU6050_Cal_Angle(void);

typedef struct {
	float x,y,z;
}Acc;

typedef struct {
	float x,y,z;
}Gyr;
#endif /* INC_MPU6050_H_ */
