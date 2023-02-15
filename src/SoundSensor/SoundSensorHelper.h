#ifndef SOUND_SENSOR_HELPER_H
#define SOUND_SENSOR_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

#include <Wire.h>
#include <HardwareSerial.h>

unsigned int output;
const int sampleWindow = 10;
unsigned int sample;
unsigned long millisCurrent = 0;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;
int sampleBufferValue = 0;

int analogIo()
{
    unsigned long start_time = millis();
    float PeakToPeak = 0;
    int db;
    unsigned int maximum_signal = 0;    // minimum value
    unsigned int minimum_signal = 4095; // maximum value
    while (millis() - start_time < sampleWindow)
    {
        output = analogRead(SOUND_A0_PIN);
        if (output < 4095)
        {
            if (output > maximum_signal)
            {
                maximum_signal = output;
            }
            else if (output < minimum_signal)
            {
                minimum_signal = output;
            }
        }
    }
    PeakToPeak = maximum_signal - minimum_signal;
    db = map(PeakToPeak, 15, 500, 24, 120);
    return db;
}

int digitalIo()
{
    sampleBufferValue = 0;
    millisElapsed = 0;
    int db;
    while (millisElapsed < sampleWindow)
    {
        millisCurrent = millis();
        if (digitalRead(SOUND_D0_PIN) == LOW)
            sampleBufferValue++;
        millisElapsed = millisCurrent - millisLast;
    }
    millisLast = millisCurrent;
    db = map(sampleBufferValue, 0, 15000, 20, 120);
    return db;
}

void soundSensorSetup()
{
    pinMode(SOUND_A0_PIN, INPUT);
    pinMode(SOUND_D0_PIN, INPUT);
    MN_DEBUGLN_F("[OK] Sound sensor setup!");
}

void soundSensorLoop()
{
    if (sound_sensor_mutex)
    {
        temp_sound_db = "";
        for (int i = 0; i < SOUND_SAMPLE_POINTS; i++)
        {
            sound_sensor_buffer[i][0] = digitalIo();
            temp_sound_db += digitalIo();
            temp_sound_db += ",";
            if (SOUND_SAMPLE_POINTS - 1 == i)
            {
                sound_sensor_mutex = false;
            }
            delay(ONE_SEC / SOUND_SAMPLING_RATE);
        }
    }
    else
    {
        delay(10);
    }
}

#endif