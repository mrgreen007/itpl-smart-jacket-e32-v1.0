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

    Serial.begin(115200);
    while (!Serial)
        delay(10);

    MN_DEBUGLN("Adafruit MPU6050 test!");

    // Try to initialize!
    if (!mpu.begin())
    {
        MN_DEBUGLN("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }
    MN_DEBUGLN("MPU6050 Found!");

    // setupt motion detection
    mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
    mpu.setMotionDetectionThreshold(1);
    mpu.setMotionDetectionDuration(20);
    mpu.setInterruptPinLatch(true); // Keep it latched.  Will turn off when reinitialized.
    mpu.setInterruptPinPolarity(true);
    mpu.setMotionInterrupt(true);

    MN_DEBUGLN("");
    delay(100);
}

void gyroAcceleroLoop()
{
    if (mpu.getMotionInterruptStatus())
    {
        /* Get new sensor events with the readings */
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        MN_DEBUGLN(" ");
        for (int i = 0; i < GA_SAMPLE_POINTS; i++)
        {
            if (gyro_accelero_mutex)
            {
                /*
                TODO: assign values to the buffer array
                eg: gyro_accelero_buffer[i][j] = some_value
                */
                gyro_accelero_buffer[i][0] = a.acceleration.x;
                gyro_accelero_buffer[i][1] = a.acceleration.y;
                gyro_accelero_buffer[i][2] = a.acceleration.z;
                gyro_accelero_buffer[i][3] = g.gyro.x;
                gyro_accelero_buffer[i][4] = g.gyro.y;
                gyro_accelero_buffer[i][5] = g.gyro.z;

                MN_DEBUG("GyroAccelero Loop : ");
                MN_DEBUG(i);

                if (GA_SAMPLE_POINTS - 1 == i)
                {
                    gyro_accelero_mutex = false;
                }

                delay(ONE_SEC / GA_SAMPLING_RATE);
            }
            else
            {
                delay(10);
            }
        }
        MN_DEBUG("AccelX:");
        MN_DEBUG(a.acceleration.x);
        MN_DEBUG("  AccelY:");
        MN_DEBUG(a.acceleration.y);
        MN_DEBUG("  AccelZ:");
        MN_DEBUG(a.acceleration.z);
        MN_DEBUG("  GyroX:");
        MN_DEBUG(g.gyro.x);
        MN_DEBUG("  GyroY:");
        MN_DEBUG(g.gyro.y);
        MN_DEBUG("  GyroZ:");
        MN_DEBUG(g.gyro.z);
    }
}

#endif