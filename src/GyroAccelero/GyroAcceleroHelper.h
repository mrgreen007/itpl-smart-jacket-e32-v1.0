#ifndef GYRO_ACCELERO_HELPER_H
#define GYRO_ACCELERO_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

void gyroAcceleroSetup()
{
    MN_DEBUGLN("GyroAccelero Setup");
}

void gyroAcceleroLoop()
{
    for (int i = 0; i < GA_SAMPLE_POINTS; i++)
    {
        if (gyro_accelero_mutex)
        {
            /*
            TODO: assign values to the buffer array
            eg: gyro_accelero_buffer[i][j] = some_value
            */

            MN_DEBUG("GyroAccelero Loop : ");
            MN_DEBUGLN(i);

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
}

#endif