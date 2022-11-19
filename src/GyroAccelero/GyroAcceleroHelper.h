#ifndef GYRO_ACCELERO_HELPER_H
#define GYRO_ACCELERO_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void testSetup()
{
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    Serial.print("Accelerometer range set to: ");
    switch (mpu.getAccelerometerRange())
    {
    case MPU6050_RANGE_2_G:
        Serial.println("+-2G");
        break;
    case MPU6050_RANGE_4_G:
        Serial.println("+-4G");
        break;
    case MPU6050_RANGE_8_G:
        Serial.println("+-8G");
        break;
    case MPU6050_RANGE_16_G:
        Serial.println("+-16G");
        break;
    }
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    Serial.print("Gyro range set to: ");
    switch (mpu.getGyroRange())
    {
    case MPU6050_RANGE_250_DEG:
        Serial.println("+- 250 deg/s");
        break;
    case MPU6050_RANGE_500_DEG:
        Serial.println("+- 500 deg/s");
        break;
    case MPU6050_RANGE_1000_DEG:
        Serial.println("+- 1000 deg/s");
        break;
    case MPU6050_RANGE_2000_DEG:
        Serial.println("+- 2000 deg/s");
        break;
    }

    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    Serial.print("Filter bandwidth set to: ");
    switch (mpu.getFilterBandwidth())
    {
    case MPU6050_BAND_260_HZ:
        Serial.println("260 Hz");
        break;
    case MPU6050_BAND_184_HZ:
        Serial.println("184 Hz");
        break;
    case MPU6050_BAND_94_HZ:
        Serial.println("94 Hz");
        break;
    case MPU6050_BAND_44_HZ:
        Serial.println("44 Hz");
        break;
    case MPU6050_BAND_21_HZ:
        Serial.println("21 Hz");
        break;
    case MPU6050_BAND_10_HZ:
        Serial.println("10 Hz");
        break;
    case MPU6050_BAND_5_HZ:
        Serial.println("5 Hz");
        break;
    }

    Serial.println("");
    delay(100);
}

void gyroAcceleroSetup()
{
    MN_DEBUGLN("GyroAccelero Setup");

    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(100);
        }
    }
    Serial.println("MPU6050 Found!");

    testSetup();
}

void testLoop()
{
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    /* Print out the values */
    Serial.print("Acceleration X: ");
    Serial.print(a.acceleration.x);
    Serial.print(", Y: ");
    Serial.print(a.acceleration.y);
    Serial.print(", Z: ");
    Serial.print(a.acceleration.z);
    Serial.println(" m/s^2");

    Serial.print("Rotation X: ");
    Serial.print(g.gyro.x);
    Serial.print(", Y: ");
    Serial.print(g.gyro.y);
    Serial.print(", Z: ");
    Serial.print(g.gyro.z);
    Serial.println(" rad/s");

    Serial.print("Temperature: ");
    Serial.print(temp.temperature);
    Serial.println(" degC");

    Serial.println("");
    delay(500);
}

void gyroAcceleroLoop()
{
    /*if (mpu.getMotionInterruptStatus())
    {
        // Get new sensor events with the readings
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        MN_DEBUGLN(" ");
        for (int i = 0; i < GA_SAMPLE_POINTS; i++)
        {
            if (gyro_accelero_mutex)
            {
                // gyro_accelero_buffer[i][0] = a.acceleration.x;
                // gyro_accelero_buffer[i][1] = a.acceleration.y;
                // gyro_accelero_buffer[i][2] = a.acceleration.z;
                // gyro_accelero_buffer[i][3] = g.gyro.x;
                // gyro_accelero_buffer[i][4] = g.gyro.y;
                // gyro_accelero_buffer[i][5] = g.gyro.z;

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
    }*/
    testLoop();
}

#endif