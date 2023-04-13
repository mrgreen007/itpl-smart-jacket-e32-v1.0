#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <ArduinoJson.h>

#define MAIN_DEBUG
#define TEST

#ifdef MAIN_DEBUG
#define MN_DEBUG(x) Serial.print(x)
#define MN_DEBUGLN(x) Serial.println(x)
#define MN_DEBUG_F(x) Serial.print(F(x))
#define MN_DEBUGLN_F(x) Serial.println(F(x))
#else
#define MN_DEBUG(x)
#define MN_DEBUGLN(x)
#define MN_DEBUG_F(x)
#define MN_DEBUGLN_F(x)
#endif

#define CORE_0 0
#define CORE_1 1

#define LED_PIN 2
#define GYRO_ACCELERO_SDA_PIN 21
#define GYRO_ACCELERO_SCL_PIN 22
#define TEMP_HUM_PIN 4
#define SOUND_A0_PIN 35
#define SOUND_D0_PIN 34
#define GPS_RX_PIN 17
#define GPS_TX_PIN 16
#define RFID_SDA_PIN 5
#define RFID_RST_PIN 27
#define BUZZER_PIN 32
#define PUSH_BUTTON_PIN 13

// Editable
#define GA_SAMPLING_RATE 5        // In Hz [max value: 1000]
#define GPS_SAMPLING_RATE 5       // In Hz [max value: 1000]
#define SOUND_SAMPLING_RATE 5     // In Hz [max value: 1000]
#define SERVER_SYNC_INTERVAL 5000 // In ms [min value: 1000]

// Non-editable
#define ONE_SEC 1000
#define BUFFER_TIME (SERVER_SYNC_INTERVAL / ONE_SEC) // In sec
#define GA_SAMPLE_POINTS (GA_SAMPLING_RATE * BUFFER_TIME)
#define GPS_SAMPLE_POINTS (GPS_SAMPLING_RATE * BUFFER_TIME)
#define SOUND_SAMPLE_POINTS (SOUND_SAMPLING_RATE * BUFFER_TIME)

// Firebase creds
#ifdef TEST
// For testing
#define FIREBASE_HOST "https://data-10cce-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "XLEA8AwVcE8jibJd2gBWMtL9Yna5vRHUH1CNch1A"
#else
#define FIREBASE_HOST "https://itpl-smart-jacket-v1-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "sMgJhFByyBzpDk0hQc5NdzVXAzVNDpgtqe75uKcz"
#endif

#endif