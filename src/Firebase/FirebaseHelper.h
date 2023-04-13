#ifndef FIREBASE_HELPER_H
#define FIREBASE_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"
#include <Firebase_ESP_Client.h>

#define EN_CALLBACK

FirebaseData firebaseData1;
FirebaseAuth auth;
FirebaseConfig config;

String fb_path = "";
String fb_stream_path = "";

#ifdef EN_CALLBACK
void extractData(FirebaseStream &data)
#else
void extractData(FirebaseData &data)
#endif
{
    MN_DEBUG_F("Value: ");
    MN_DEBUGLN(data.to<String>());
}

#ifdef EN_CALLBACK
void streamCallback(FirebaseStream data)
{
  extractData(data);
}

void streamTimeoutCallback(bool timeout)
{
  if (timeout)
  {
    MN_DEBUGLN_F("[TIME-OUT]Stream timeout, resume streaming...");
  }
}
#endif

void firebaseSetup()
{
    config.database_url = F(FIREBASE_HOST);
    config.signer.tokens.legacy_token = FIREBASE_AUTH;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    if (!Firebase.RTDB.beginStream(&firebaseData1, fb_stream_path))
    {
        MN_DEBUG_F("[E] Stream begin error: ");
        MN_DEBUGLN(firebaseData1.errorReason().c_str());
    }

    #ifdef EN_CALLBACK
    // Setup streaming callback function [*]
    Firebase.RTDB.setStreamCallback(&firebaseData1, streamCallback, streamTimeoutCallback);
    #endif

    delay(100);
    MN_DEBUGLN_F("[OK] Firebase setup!");
}

#ifndef EN_CALLBACK
void listenStream()
{
    if (Firebase.ready())
    {
        if (!Firebase.RTDB.readStream(&firebaseData1))
        {
            MN_DEBUG_F("[E] Stream Read Error: ");
            MN_DEBUGLN(firebaseData1.errorReason());
        }

        if (firebaseData1.streamTimeout())
        {
            MN_DEBUGLN_F("[TIME-OUT]Stream timeout, resume streaming...");
        }

        if (firebaseData1.streamAvailable())
        {
            extractData(firebaseData1);
        }
    }
}
#endif

bool fbSilentUpdate(FirebaseJson &json)
{
    if (Firebase.RTDB.updateNodeSilentAsync(&firebaseData1, fb_path, &json))
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

/*
bool jsonSetter_old(FirebaseJson &json)
{
    String temperature = temp_temperature;
    String humidity = temp_humidity;
    int str_len = temperature.length();

    if (str_len == 0)
    {
        String x = "x.x";
        for (int i = 0; i < 25; i++)
        {
            temperature += x;
            temperature += ",";
            humidity += x;
            humidity += ",";
        }
    }
    else if (temperature[str_len - 1] != ',')
    {
        String t = temperature;
        String h = humidity;
        temperature = "";
        humidity = "";

        for (int i = 0; i < 25; i++)
        {
            temperature += t;
            temperature += ",";
            humidity += h;
            humidity += ",";
        }
    }

    if (gps_index_counter != 0)
    {
        String lat_last_val = String(gps_buffer[gps_index_counter - 1][0], 6U);
        String lon_last_val = String(gps_buffer[gps_index_counter - 1][1], 6U);
        String alt_last_val = String(gps_buffer[gps_index_counter - 1][2], 6U);

        for (int i = gps_index_counter; i < GPS_SAMPLE_POINTS; i++)
        {
            temp_gps_latitude += lat_last_val;
            temp_gps_latitude += ",";
            temp_gps_longitude += lon_last_val;
            temp_gps_longitude += ",";
            temp_gps_altitude += alt_last_val;
            temp_gps_altitude += ",";
        }

        gps_index_counter = 0;
    }
    else if (gps_index_counter == 0 && temp_gps_latitude == "")
    {
        String x = "0.0";
        for (int i = 0; i < GPS_SAMPLE_POINTS; i++)
        {
            temp_gps_latitude += x;
            temp_gps_latitude += ",";
            temp_gps_longitude += x;
            temp_gps_longitude += ",";
            temp_gps_altitude += x;
            temp_gps_altitude += ",";
        }
    }

    MN_DEBUGLN(temp_accelero_X);
    MN_DEBUGLN(temp_accelero_Y);
    MN_DEBUGLN(temp_accelero_Z);
    MN_DEBUGLN(temp_gyro_X);
    MN_DEBUGLN(temp_gyro_Y);
    MN_DEBUGLN(temp_gyro_Z);

    MN_DEBUGLN(temp_gps_latitude);
    MN_DEBUGLN(temp_gps_longitude);
    MN_DEBUGLN(temp_gps_altitude);

    MN_DEBUGLN(temperature);
    MN_DEBUGLN(humidity);

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

    json.set("TEM", temperature);
    json.set("HUM", humidity);

    json.set("SNL", temp_sound_db);

    return true;
}
*/

/*bool displaySetter(FirebaseJson &json, const String &timestamp) // Tem and hum
{
    // FirebaseJson temphum;
    // temphum.set("TEM", "28.20");
    // temphum.set("HUM", "66.20");
    // json.set(fb_path+"/display/"+timestamp, temphum);

    json.set(fb_path+"/display/"+timestamp+"/TEM", "temp_temperature");
    json.set(fb_path+"/display/"+timestamp+"/HUM", "temp_humidity");
    return true;
}

bool liveSetter(FirebaseJson &json, const String &timestamp)
{
    json.set(fb_path+"/live/"+timestamp+"/ALT", temp_gps_altitude);
    json.set(fb_path+"/live/"+timestamp+"/LAT", temp_gps_latitude);
    json.set(fb_path+"/live/"+timestamp+"/LON", temp_gps_longitude);
    return true;
}

bool predictsetter(FirebaseJson &json, const String &timestamp)
{
    // FirebaseJson predict;
    // FirebaseJson altitudes;
    // altitudes.set("A_X", "-0.30,-0.30,-0.30,-0.29,-0.30,-0.30,-0.29,-0.30,-0.30,-0.31,-0.31,-0.29,-0.31,-0.30,-0.31,-0.29,-0.30,-0.29,-0.33,-0.29,-0.30,-0.29,-0.30,-0.30,-0.29");
    // altitudes.set("A_Y", "-0.19,-0.21,-0.21,-0.20,-0.21,-0.20,-0.22,-0.21,-0.20,-0.19,-0.19,-0.22,-0.20,-0.20,-0.19,-0.21,-0.21,-0.20,-0.21,-0.20,-0.20,-0.19,-0.21,-0.21,-0.21");
    // altitudes.set("A_Z", "9.87,9.84,9.83,9.85,9.87,9.85,9.84,9.89,9.83,9.89,9.88,9.89,9.83,9.86,9.85,9.84,9.85,9.88,9.88,9.86,9.85,9.86,9.87,9.84,9.85");
    // altitudes.set("G_X", "-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04,-0.04");
    // altitudes.set("G_Y", "-0.01,-0.01,-0.00,-0.01,-0.00,-0.01,-0.00,-0.00,-0.00,-0.01,-0.01,-0.00,-0.00,-0.00,-0.01,-0.01,-0.01,-0.00,-0.01,-0.00,-0.00,-0.00,-0.00,-0.00,-0.00");
    // altitudes.set("G_Z", "0.01,0.01,0.02,0.01,0.01,0.01,0.01,0.01,0.02,0.01,0.01,0.02,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.02,0.01,0.02,0.02,0.01,0.01");
    // predict.set(timestamp, altitudes);
    // json.set("predict", predict);

    json.set(fb_path+"/predict/"+timestamp+"/A_X", temp_accelero_X);
    json.set(fb_path+"/predict/"+timestamp+"/A_Y", temp_accelero_Y);
    json.set(fb_path+"/predict/"+timestamp+"/A_Z", temp_accelero_Z);
    json.set(fb_path+"/predict/"+timestamp+"/G_X", temp_gyro_X);
    json.set(fb_path+"/predict/"+timestamp+"/G_Y", temp_gyro_Y);
    json.set(fb_path+"/predict/"+timestamp+"/G_Z", temp_gyro_Z);
    return true;
}

bool rfidsetter(FirebaseJson &json)
{
    json.set(fb_path+"/rfid", "xyz");
    return true;
}

bool soundsetter(FirebaseJson &json, const String &timestamp)
{
    // FirebaseJson sound;
    // FirebaseJson snl;
    // snl.set("SNL", "42,61,62,68,69,61,62,67,68,66,62,61,68,68,56,62,62,68,68,58,58,59,61,68,63");
    // sound.set(timestamp, snl);
    // json.set("sound", sound);

    json.set(fb_path+"/sound/"+timestamp+"/SNL", temp_sound_db);
    return true;
}

double rand_double()
{
    return ((double)rand()) / ((double)RAND_MAX);
}*/

bool jsonSetter(FirebaseJson &json)
{
    String temperature = temp_temperature;
    String humidity = temp_humidity;
    temperature += ",";
    humidity += ",";

    json.set("TEM", temperature);
    json.set("HUM", humidity);

    json.set("A_X", temp_accelero_X);
    json.set("A_Y", temp_accelero_Y);
    json.set("A_Z", temp_accelero_Z);
    json.set("G_X", temp_gyro_X);
    json.set("G_Y", temp_gyro_Y);
    json.set("G_Z", temp_gyro_Z);

    json.set("LAT", temp_gps_latitude);
    json.set("LON", temp_gps_longitude);
    json.set("ALT", temp_gps_altitude);

    json.set("SNL", temp_sound_db);

    json.set("rfid", rfid_tag_id);
    return true;
}

bool updateDB(const String &timestamp)
{
    FirebaseJson payload;

    if (jsonSetter(payload))
    {
        fb_path = "/Devices/";
        fb_path += device_id;
        fb_path += "/";
        fb_path += "sensordata";
        fb_path += "/";
        fb_path += timestamp;
        return fbSilentUpdate(payload);
    }
    return false;
}

#endif