#ifndef GPS_HELPER_H
#define GPS_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

/*#include <TinyGPS++.h>
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
*/
#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN); // RX, TX
char buffer[100];

void updateValues(int i)
{
  if (gps.location.isUpdated())
  {
    /*double lat = gps.location.lat();
    double lng = gps.location.lng();

    double altitude = gps.altitude.meters();

    int year = gps.date.year();
    int month = gps.date.month();
    int day = gps.date.day();

    int hour = gps.time.hour();
    int minute = gps.time.minute();
    int second = gps.time.second();

    snprintf(buffer, sizeof(buffer),
             "Latitude: %.8f, Longitude: %.8f, Altitude: %.2f m, "
             "Date/Time: %d-%02d-%02d %02d:%02d:%02d",
             lat, lng, altitude, year, month, day, hour, minute, second);

    Serial.println(buffer);*/

    gps_buffer[i][0] = gps.location.lat();
    temp_gps_latitude += String(gps.location.lat());
    temp_gps_latitude += ",";

    gps_buffer[i][1] = gps.location.lng();
    temp_gps_longitude += String(gps.location.lng());
    temp_gps_longitude += ",";

    gps_buffer[i][2] = gps.altitude.meters();
    temp_gps_altitude += String(gps.altitude.meters());
    temp_gps_altitude += ",";
  }
}

void gpsSetup()
{
  gpsSerial.begin(9600);
  Serial.println("\nStarting...");
}

void gpsLoop()
{

  if (gps_mutex)
  {
    temp_gps_latitude = "";
    temp_gps_longitude = "";
    temp_gps_altitude = "";
    for (int i = 0; i < GPS_SAMPLE_POINTS; i++)
    {
      while(gpsSerial.available() > 0)
      {
        if (gps.encode(gpsSerial.read()))
        {
          updateValues(i);
          break;
        }
      }

      MN_DEBUG("GPS Loop : ");
      MN_DEBUGLN(i);

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