/*
 * mpu6050.c
 *
 *  Created on: Sep 27, 2020
 *      Author: DELL
 */
#include <stdio.h>
#include <math.h>
#include "mpu6050.h"
extern I2C_HandleTypeDef hi2c1;
uint8_t device_address = MPU_6050_ADDRESS;
int16_t rawAccX, rawAccY,rawAccZ,rawGyroX,rawGyroY,rawGyroZ,rawTemp;
float ax, ay, az, gx, gy, gz,temp;
double theta, phi, omega;

Acc acc;
Gyr gyr;

void MPU6050_Init(void){
	uint8_t check;
	uint8_t data;
	HAL_I2C_Mem_Read(&hi2c1,(uint16_t) device_address, WHO_AM_I_REG, 1, &check, 1, 1000);
	if (check==104) {
		data=0;
		HAL_I2C_Mem_Write(&hi2c1,(uint16_t) device_address, PWR_MGMT_1_REG, 1, &data, 1, 1000);
		data=0x07;
		HAL_I2C_Mem_Write(&hi2c1,(uint16_t) device_address, SMPLRT_DIV_REG, 1, &data, 1, 1000);
		data=0x00;
		HAL_I2C_Mem_Write(&hi2c1,(uint16_t) device_address, ACCEL_CONFIG_REG, 1, &data, 1, 1000);
		data=0x00;
		HAL_I2C_Mem_Write(&hi2c1,(uint16_t) device_address, GYRO_CONFIG_REG, 1, &data, 1, 1000);
		data=0x01;
		HAL_I2C_Mem_Write(&hi2c1,(uint16_t) device_address, INT_ENABLE_REG, 1, &data, 1, 1000);
		data=0x00;
		HAL_I2C_Mem_Write(&hi2c1,(uint16_t) device_address, USER_CONTROL_REG, 1, &data, 1, 1000);
			}
}

void MPU6050_Read_Data(void){
		uint8_t rawdata[14];
		// Read 6 BYTES of data starting from ACCEL_XOUT_H register
		HAL_I2C_Mem_Read(&hi2c1, (uint16_t)device_address, ACCEL_XOUT_H_REG, 1,rawdata, 14, 1000);
		rawAccX=(int16_t)(rawdata[0]<<8 | rawdata[1]);
		rawAccY=(int16_t)(rawdata[2]<<8 | rawdata[3]);
		rawAccZ=(int16_t)(rawdata[4]<<8 | rawdata[5]);
		rawTemp=(int16_t)(rawdata[6]<<8 | rawdata[7]);
		rawGyroX=(int16_t)(rawdata[8]<<8 | rawdata[9]);
		rawGyroY=(int16_t)(rawdata[10]<<8 | rawdata[11]);
		rawGyroZ=(int16_t)(rawdata[12]<<8 | rawdata[13]);

		acc.x = (float)rawAccX/16384.0;
		acc.y = (float)rawAccY/16384.0;
		acc.z = (float)rawAccZ/16384.0;

		temp = (rawTemp+12412.0)/340.0;

		gyr.x = (float)rawGyroX/131.0;
		gyr.y = (float)rawGyroY/131.0;
		gyr.z = (float)rawGyroZ/131.0;


}
double roll, pre_roll = 0.0 , pitch, pre_pitch = 0.0;
void MPU6050_Angle(void){
	roll =  a*(pre_roll + (double)gyr.x*0.01)+(1 - a)*(atan2((double)acc.y, (double)acc.z)*(180.0)/PI);
	pre_roll = roll;
}
