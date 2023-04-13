#ifndef TIME_HELPER_H
#define TIME_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

#include <Arduino.h>
#include <WiFi.h>
#include <string.h>
#include <stdio.h>
#include "TimeLib.h"
#include "time.h"
#include "TinyGPS++.h"
#include <SoftwareSerial.h>

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;
const int daylightOffset_sec = 0;

struct tm timeinfo;

void getLocalTime()
{
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
}

void makeTimestamp(char time_str[])
{
    int i = 0;
    char hr[3], min[4], sec[10], yr[5], mn[3], d[3];
    sprintf(yr, "%d", year());
    strcat(time_str, yr);
    strcat(time_str, "-");
    sprintf(mn, "%d", month() + 1);
    if (month() + 1 < 10)
    {
        strcat(time_str, "0");
        strcat(time_str, mn);
    }
    else
        strcat(time_str, mn);
    strcat(time_str, "-");
    sprintf(d, "%d", day());
    if (day() < 10)
    {
        strcat(time_str, "0");
        strcat(time_str, d);
    }
    else
        strcat(time_str, d);
    strcat(time_str, " ");
    sprintf(hr, "%d", hour());
    if (hour() < 10)
    {
        strcat(time_str, "0");
        strcat(time_str, hr);
    }
    else
        strcat(time_str, hr);
    sprintf(min, "%d", minute());
    strcat(time_str, ":");
    if (minute() < 10)
    {
        strcat(time_str, "0");
        strcat(time_str, min);
    }
    else
        strcat(time_str, min);
    sprintf(sec, "%f", (float)second());
    strcat(time_str, ":");
    while (sec[i] != '\0')
    {
        if (sec[i] == '.')
        {
            sec[i] = ':';
        }
        i++;
    }
    if (second() < 10)
    {
        strcat(time_str, "0");
        strcat(time_str, sec);
    }
    else
        strcat(time_str, sec);
}

void ConfigTime() // Call this function once to configure the time
{
    // if (gpsSerial.available() > 0)
    // {
    //     if (gps.encode(gpsSerial.read()))
    //     {
    //         if (gps.time.isValid())
    //         {
    //             Serial.println("Fetching the time from GPS and storing in time library");
    //             setTime((int)gps.time.hour(), (int)gps.time.minute(), (int)gps.time.second(), (int)gps.date.day(), (int)gps.date.month(), (int)gps.date.year());
    //         }
    //     }
    // }

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    getLocalTime();
    Serial.println("Fetching the time from NTP server and storing in time library");
    setTime(timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_mday, timeinfo.tm_mon, timeinfo.tm_year + 1900);
}

String getTimestamp() // Call this function to get the current time
{
    char time_str[27] = "";
    if (timeStatus() != timeNotSet)
    {
        makeTimestamp(time_str);
        return (String)time_str;
    }
    return String(millis());
}

void timeSetup()
{
    // setSyncProvider(timeUpdateManager);
    // setSyncInterval(12 * 3600); // 12*3600 sec interval for system time sync

    ConfigTime();
    if (timeStatus() != timeSet)
    {
        MN_DEBUGLN_F("[Fail] Unable to sync Time!");
    }
    else
    {
        MN_DEBUGLN_F("[OK] Time setup!");
    }
}

#endif