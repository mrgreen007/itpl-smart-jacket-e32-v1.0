#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define MAIN_DEBUG

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

// Editable
#define GA_SAMPLING_RATE 5        // In Hz [max value: 1000]
#define GPS_SAMPLING_RATE 5       // In Hz [max value: 1000]
#define SERVER_SYNC_INTERVAL 5000 // In ms [min value: 1000]

// Non-editable
#define ONE_SEC 1000
#define BUFFER_TIME (SERVER_SYNC_INTERVAL / ONE_SEC) // In sec
#define GA_SAMPLE_POINTS (GA_SAMPLING_RATE * BUFFER_TIME)
#define GPS_SAMPLE_POINTS (GPS_SAMPLING_RATE * BUFFER_TIME)

// Firebase creds
#define FIREBASE_HOST "itpl-smart-jacket-v1-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "sMgJhFByyBzpDk0hQc5NdzVXAzVNDpgtqe75uKcz"

#endif