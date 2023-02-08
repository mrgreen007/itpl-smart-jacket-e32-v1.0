#ifndef FIREBASE_HELPER_H
#define FIREBASE_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"
#include <Firebase_ESP_Client.h>

FirebaseData firebaseData1;
FirebaseAuth auth;
FirebaseConfig config;

String path = "";

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
    int str_len = temp_temperature.length();
    if(str_len == 0)
    {
        String x = "x.x";
        for(int i=0; i<25; i++)
        {
            temp_temperature += x;
            temp_temperature += ",";
            temp_humidity += x;
            temp_humidity += ",";
        }
    }
    else if(temp_temperature[str_len-1] != ',')
    {
        String t = temp_temperature;
        String h = temp_humidity;
        temp_temperature = "";
        temp_humidity = "";

        for (int i=0; i<25; i++)
        {
            temp_temperature += t;
            temp_temperature += ",";
            temp_humidity += h;
            temp_humidity += ",";
        }
    }
    

    MN_DEBUGLN(temp_accelero_X);
    MN_DEBUGLN(temp_accelero_Y);
    MN_DEBUGLN(temp_accelero_Z);
    MN_DEBUGLN(temp_gyro_X);
    MN_DEBUGLN(temp_gyro_Y);
    MN_DEBUGLN(temp_gyro_Z);

    MN_DEBUGLN(temp_gps_altitude);
    MN_DEBUGLN(temp_gps_latitude);
    MN_DEBUGLN(temp_gps_longitude);

    MN_DEBUGLN(temp_temperature);
    MN_DEBUGLN(temp_humidity);

    MN_DEBUGLN(temp_sound_db);

    json.set("A_X", temp_accelero_X);
    json.set("A_Y", temp_accelero_Y);
    json.set("A_Z", temp_accelero_Z);
    json.set("G_X", temp_gyro_X);
    json.set("G_Y", temp_gyro_Y);
    json.set("G_Z", temp_gyro_Z);

    json.set("LAT", temp_gps_latitude);
    json.set("LON", temp_gps_longitude);
    json.set("ALT", temp_gps_altitude);

    json.set("TEM", temp_temperature);
    json.set("HUM", temp_humidity);

    json.set("SNL", temp_sound_db);

    return true;
}

bool updateDB(const String &timestamp)
{
    FirebaseJson payload;
    if (jsonSetter(payload))
    {
        path = "/";
        path += timestamp;
         return true;
        //return fbSilentUpdate(payload);
    }
    return false;
}

#endif