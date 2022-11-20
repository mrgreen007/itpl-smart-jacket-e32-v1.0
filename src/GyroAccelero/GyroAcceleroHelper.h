#ifndef GYRO_ACCELERO_HELPER_H
#define GYRO_ACCELERO_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void gyroAcceleroSetup()
{
    MN_DEBUGLN("GyroAccelero Setup");

    if (!mpu.begin())
    {
        MN_DEBUGLN("Failed to find MPU6050 chip");
        while (1)
        {
            delay(100);
        }
    }
    MN_DEBUGLN("MPU6050 Found!");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    delay(50);
}

void gyroAcceleroLoop()
{
    if (gyro_accelero_mutex)
    {
        start_timestamp = millis(); // should be modified
        for (int i = 0; i < GA_SAMPLE_POINTS; i++)
        {

            sensors_event_t a, g, temp;
            mpu.getEvent(&a, &g, &temp);

            gyro_accelero_buffer[i][0] = a.acceleration.x;
            temp_accelero_X += a.acceleration.x;

            gyro_accelero_buffer[i][1] = a.acceleration.y;
            temp_accelero_Y += a.acceleration.y;

            gyro_accelero_buffer[i][2] = a.acceleration.z;
            temp_accelero_Z += a.acceleration.z;

            gyro_accelero_buffer[i][3] = g.gyro.x;
            temp_gyro_X += g.gyro.x;

            gyro_accelero_buffer[i][4] = g.gyro.y;
            temp_gyro_Y += g.gyro.y;

            gyro_accelero_buffer[i][5] = g.gyro.z;
            temp_gyro_Z += g.gyro.z;

            MN_DEBUG("GyroAccelero Loop : ");
            MN_DEBUG(i);

            if (GA_SAMPLE_POINTS - 1 == i)
            {
                end_timestamp = millis(); // should be modified
                gyro_accelero_mutex = false;
            }

            delay(ONE_SEC / GA_SAMPLING_RATE);
        }
    }
    else
    {
        delay(10);
    }
}

#endif