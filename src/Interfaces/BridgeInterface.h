#ifndef BRIDGE_INTERFACE_H
#define BRIDGE_INTERFACE_H

#include "config.h"

float gyro_accelero_buffer[GA_SAMPLE_POINTS][6] = {0.0};
bool gyro_accelero_mutex = true;
float gps_buffer[GPS_SAMPLE_POINTS][3] = {0.0};
bool gps_mutex = true;

time_t start_timestamp = 0;
time_t end_timestamp = 0;

// temppp
String temp_accelero_X = "";
String temp_accelero_Y = "";
String temp_accelero_Z = "";
String temp_gyro_X = "";
String temp_gyro_Y = "";
String temp_gyro_Z = "";

#endif