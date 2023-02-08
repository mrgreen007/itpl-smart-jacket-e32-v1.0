#ifndef GPS_HELPER_H
#define GPS_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial SerialGPS(GPS_TX_PIN, GPS_RX_PIN);     //RX(GPS Tx pin), TX(GPS Rx pin)

void gpsSetup()
{
    MN_DEBUGLN("GPS Setup");
    SerialGPS.begin(9600);
    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
        MN_DEBUGLN("GPS NOT DETECTED!");
        //while (true);
    }
    MN_DEBUGLN("GPS Detected");
    delay(50);
}

void gpsLoop()
{
    if (gps_mutex)
    {
        temp_gps_latitude = "";
        temp_gps_longitude = "";
        temp_gps_altitude = "";
        start_timestamp = millis(); // should be modified
        for (int i = 0; i < GPS_SAMPLE_POINTS; i++)
        {
            gps_buffer[i][0] = gps.location.lat();
            temp_gps_latitude += gps.location.lat();
            temp_gps_latitude += ",";

            gps_buffer[i][1] = gps.location.lng();
            temp_gps_longitude += gps.location.lng();
            temp_gps_longitude += ",";

            gps_buffer[i][2] = gps.altitude.meters();
            temp_gps_altitude += gps.altitude.meters();
            temp_gps_altitude += ",";

            /*
            TODO: assign values to the buffer array
            eg: gps_buffer[i][j] = some_value
            */

            // MN_DEBUG("GPS Loop : ");
            // MN_DEBUGLN(i);

            if (GPS_SAMPLE_POINTS - 1 == i)
            {
                gps_mutex = false;
            }
            delay(ONE_SEC / GPS_SAMPLING_RATE);
        }
    }
    else
    {
        delay(10);
    }
}

#endif // !GPS_HELPER_H