#ifndef BRIDGE_INTERFACE_H
#define BRIDGE_INTERFACE_H

#include "config.h"

#define LED_PIN 2

// Editable
#define GA_SAMPLING_RATE 50       // In Hz [max value: 1000]
#define GPS_SAMPLING_RATE 50      // In Hz [max value: 1000]
#define SERVER_SYNC_INTERVAL 5000 // In ms [min value: 1000]

// Non-editable
#define ONE_SEC 1000
#define BUFFER_TIME (SERVER_SYNC_INTERVAL / ONE_SEC) // In sec
#define GA_SAMPLE_POINTS (GA_SAMPLING_RATE * BUFFER_TIME)
#define GPS_SAMPLE_POINTS (GPS_SAMPLING_RATE * BUFFER_TIME)

float gyro_accelero_buffer[GA_SAMPLE_POINTS][6] = {0.0};
bool gyro_accelero_mutex = true;
float gps_buffer[GPS_SAMPLE_POINTS][3] = {0.0};
bool gps_mutex = true;

#endif