#ifndef GYRO_ACCELERO_HELPER_H
#define GYRO_ACCELERO_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"
#include "./Time/TimeHelper.h"

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void gyroAcceleroSetup()
{
    if (!mpu.begin())
    {
        MN_DEBUGLN_F("[WAITING] Failed to find MPU6050 chip!");
        while (1)
        {
            delay(100);
        }
    }
    MN_DEBUGLN_F("[OK] GyroAccelero setup!");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    delay(50);
}

void gyroAcceleroLoop()
{
    if (gyro_accelero_mutex)
    {
        temp_accelero_X = "";
        temp_accelero_Y = "";
        temp_accelero_Z = "";
        temp_gyro_X = "";
        temp_gyro_Y = "";
        temp_gyro_Z = "";
        //start_timestamp = getTimestamp();
        start_timestamp = millis();
        for (int i = 0; i < GA_SAMPLE_POINTS; i++)
        {

            sensors_event_t a, g, temp;
            mpu.getEvent(&a, &g, &temp);

            gyro_accelero_buffer[i][0] = a.acceleration.x;
            temp_accelero_X += a.acceleration.x;
            temp_accelero_X += ",";

            gyro_accelero_buffer[i][1] = a.acceleration.y;
            temp_accelero_Y += a.acceleration.y;
            temp_accelero_Y += ",";

            gyro_accelero_buffer[i][2] = a.acceleration.z;
            temp_accelero_Z += a.acceleration.z;
            temp_accelero_Z += ",";

            gyro_accelero_buffer[i][3] = g.gyro.x;
            temp_gyro_X += g.gyro.x;
            temp_gyro_X += ",";

            gyro_accelero_buffer[i][4] = g.gyro.y;
            temp_gyro_Y += g.gyro.y;
            temp_gyro_Y += ",";

            gyro_accelero_buffer[i][5] = g.gyro.z;
            temp_gyro_Z += g.gyro.z;
            temp_gyro_Z += ",";

            if (GA_SAMPLE_POINTS - 1 == i)
            {
                //end_timestamp = getTimestamp();
                end_timestamp = millis();
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