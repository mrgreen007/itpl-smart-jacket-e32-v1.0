#ifndef GPS_HELPER_H
#define GPS_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN); // //RX(GPS Tx pin), TX(GPS Rx pin)
char buffer[100];

int gps_index_counter = 0;

/*void updateValues_()
{
  if (gps.location.isUpdated())
  {
    double lat = gps.location.lat();
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

    Serial.println(buffer);
  }
}*/

void updateValues()
{
  if (gps.location.isValid())
  {
    // Serial.print("Lat: ");
    // Serial.print(gps.location.lat(), 6);
    // Serial.print(F(","));
    // Serial.print("Lng: ");
    // Serial.print(gps.location.lng(), 6);
    // Serial.println();

    if (gps_mutex)
    {
      if (gps_index_counter == 0)
      {
        temp_gps_latitude = "";
        temp_gps_longitude = "";
        temp_gps_altitude = "";
      }

      gps_buffer[gps_index_counter][0] = gps.location.lat();
      temp_gps_latitude += String(gps.location.lat(), 6U);
      temp_gps_latitude += ",";

      gps_buffer[gps_index_counter][1] = gps.location.lng();
      temp_gps_longitude += String(gps.location.lng(), 6U);
      temp_gps_longitude += ",";

      gps_buffer[gps_index_counter][2] = gps.altitude.meters();
      temp_gps_altitude += String(gps.altitude.meters(), 6U);
      temp_gps_altitude += ",";

      if (1 /*GPS_SAMPLE_POINTS*/ - 1 == gps_index_counter)
      {
        gps_mutex = false;
        gps_index_counter = -1;
      }
      gps_index_counter++;
    }
  }
  else
  {
    // Invalid location
  }
}

void gpsSetup()
{
  gpsSerial.begin(9600);
  MN_DEBUGLN_F("[OK] GPS setup!");
}

void gpsLoop()
{
  while (gpsSerial.available() > 0)
  {
    if (gps.encode(gpsSerial.read()))
    {
      updateValues();
    }
  }
}

#endif // !GPS_HELPER_H