#ifndef BRIDGE_INTERFACE_H
#define BRIDGE_INTERFACE_H

#include "config.h"

float gyro_accelero_buffer[GA_SAMPLE_POINTS][6] = {0.0};
bool gyro_accelero_mutex = true;
float gps_buffer[GPS_SAMPLE_POINTS][3] = {0.0};
bool gps_mutex = true;

#endif