#ifndef BRIDGE_INTERFACE_H
#define BRIDGE_INTERFACE_H

#include "config.h"

#define LED_PIN 2

#define AG_REFRESH_RATE 100       // In Hz
#define GPS_REFRESH_RATE 100      // In Hz
#define SERVER_SYNC_INTERVAL 1000 // In ms

float accelerogyro_buffer[AG_REFRESH_RATE][6] = {0};
bool accerlerogyro_mutex = true;
float gps_buffer[GPS_REFRESH_RATE][3] = {0};
bool gps_mutex = true;

#endif