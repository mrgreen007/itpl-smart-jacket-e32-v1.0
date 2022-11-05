#ifndef GPS_HELPER_H
#define GPS_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

void gpsSetup()
{
    MN_DEBUGLN("GPS Setup");
}

void gpsLoop()
{
    for (int i = 0; i < GPS_SAMPLE_POINTS; i++)
    {
        if (gps_mutex)
        {
            /*
            TODO: assign values to the buffer array
            eg: gps_buffer[i][j] = some_value
            */

            MN_DEBUG("GPS Loop : ");
            MN_DEBUGLN(i);

            if (GPS_SAMPLE_POINTS - 1 == i)
            {
                gps_mutex = false;
            }
            delay(ONE_SEC / GPS_SAMPLING_RATE);
        }
        else
        {
            delay(10);
        }
    }
}

#endif // !GPS_HELPER_H