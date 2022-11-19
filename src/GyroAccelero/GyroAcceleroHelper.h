#ifndef GYRO_ACCELERO_HELPER_H
#define GYRO_ACCELERO_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

#include "GY521.h"

GY521 sensor(0x69);

uint32_t counter = 0;

void testSetup()
{
    Wire.begin();

    delay(100);
    while (sensor.wakeup() == false)
    {
        Serial.print(millis());
        Serial.println("\tCould not connect to GY521");
        delay(1000);
    }
    sensor.setAccelSensitivity(0); // 2g
    sensor.setGyroSensitivity(0);  // 250 degrees/s

    sensor.setThrottle();
    Serial.println("start...");

    // set calibration values from calibration sketch.
    sensor.axe = 0;
    sensor.aye = 0;
    sensor.aze = 0;
    sensor.gxe = 0;
    sensor.gye = 0;
    sensor.gze = 0;
}

void gyroAcceleroSetup()
{
    MN_DEBUGLN("GyroAccelero Setup");

    testSetup();
}

void testLoop()
{
    sensor.read();
    int ax = sensor.getAccelX();
    int ay = sensor.getAccelY();
    int az = sensor.getAccelZ();
    int gx = sensor.getGyroX();
    int gy = sensor.getGyroY();
    int gz = sensor.getGyroZ();
    int t = sensor.getTemperature();

    if (counter % 10 == 0)
    {
        Serial.println("\n\tACCELEROMETER\t\tGYROSCOPE\t\tTEMPERATURE");
        Serial.println("\tax\tay\taz\tgx\tgy\tgz\tT");
    }

    Serial.print(counter);
    Serial.print('\t');
    Serial.print(ax);
    Serial.print('\t');
    Serial.print(ay);
    Serial.print('\t');
    Serial.print(az);
    Serial.print('\t');
    Serial.print(gx);
    Serial.print('\t');
    Serial.print(gy);
    Serial.print('\t');
    Serial.print(gz);
    Serial.print('\t');
    Serial.print(t);
    Serial.println();

    counter++;
    delay(1000);
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