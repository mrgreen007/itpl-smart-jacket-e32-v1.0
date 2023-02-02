#ifndef FIREBASE_HELPER_H
#define FIREBASE_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"
#include <Firebase_ESP_Client.h>

FirebaseData firebaseData1;
FirebaseAuth auth;
FirebaseConfig config;

String path = "";
float temp_value;
float hum_value;

void firebaseSetup()
{
    config.database_url = F(FIREBASE_HOST);
    config.signer.tokens.legacy_token = FIREBASE_AUTH;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}

bool fbSilentUpdate(FirebaseJson &json)
{
    if (Firebase.RTDB.updateNodeSilentAsync(&firebaseData1, path, &json)) // +Async
    {
        MN_DEBUGLN_F("[UPDATE] Successful");
    }
    else
    {
        MN_DEBUG_F("[FAIL] Fail to update :\t");
        MN_DEBUGLN(firebaseData1.errorReason());
        return false;
    }
    return true;
}

bool jsonSetter(FirebaseJson &json)
{
    MN_DEBUGLN(temp_accelero_X);
    MN_DEBUGLN(temp_accelero_Y);
    MN_DEBUGLN(temp_accelero_Z);
    MN_DEBUGLN(temp_gyro_X);
    MN_DEBUGLN(temp_gyro_Y);
    MN_DEBUGLN(temp_gyro_Z);
    MN_DEBUGLN(current_temperature);
    MN_DEBUGLN(current_humidity);

    json.set("A_X", temp_accelero_X);
    json.set("A_Y", temp_accelero_Y);
    json.set("A_Z", temp_accelero_Z);
    json.set("G_X", temp_gyro_X);
    json.set("G_Y", temp_gyro_Y);
    json.set("G_Z", temp_gyro_Z);
    if (current_temperature != -100)
    {
        json.set("Temp", current_temperature);
        temp_value = current_temperature;
    }
    else
    {
        json.set("Temp", temp_value);
    }
    if (current_humidity != -100)
    {
        json.set("Hum", current_humidity);
        hum_value = current_humidity;
    }
    else
    {
        json.set("Hum", hum_value);
    }

    return true;
}

bool updateDB(const String &timestamp)
{
    FirebaseJson payload;
    if (jsonSetter(payload))
    {
        path = "/";
        path += timestamp;
        // return true;
        return fbSilentUpdate(payload);
    }
    return false;
}

#endif