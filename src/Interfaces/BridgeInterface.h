#ifndef BRIDGE_H
#define BRIDGE_H

#include "config.h"

String device_id = "";
String rfid_id_tag = "";

float gyro_accelero_buffer[GA_SAMPLE_POINTS][6] = {0.0};
double gps_buffer[GPS_SAMPLE_POINTS][3] = {0.0};
int sound_sensor_buffer[SOUND_SAMPLE_POINTS][1] = {0};
float temp_hum_buffer[2] = {-100};

bool gyro_accelero_mutex = true;
bool gps_mutex = true;
bool sound_sensor_mutex = true;
bool led_mutex = true;

String start_timestamp = "";
String end_timestamp = "";

// temporary strings
String temp_accelero_X = "";
String temp_accelero_Y = "";
String temp_accelero_Z = "";

String temp_gyro_X = "";
String temp_gyro_Y = "";
String temp_gyro_Z = "";

String temp_gps_latitude = "";
String temp_gps_longitude = "";
String temp_gps_altitude = "";

String temp_temperature = "";
String temp_humidity = "";

String temp_sound_db = "";

#endif