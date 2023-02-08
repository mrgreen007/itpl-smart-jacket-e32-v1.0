#ifndef TEMP_HU_HELPER_H
#define TEMP_HU_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

#include "DHTesp.h"

DHTesp dht;

float getTemperature()
{
    float t = dht.getTemperature();
    if (!isnan(t))
    {
        return t;
    }
    return -100.00;
}

float getHumidity()
{
    float h = dht.getHumidity();
    if (!isnan(h))
    {
        return h;
    }
    return -100.00;
}

void tempHuSetup()
{
    MN_DEBUGLN("Temp Setup");
    dht.setup(TEMP_HUM_PIN, DHTesp::DHT22);
}

void tempHuLoop()
{
    temp_hum_buffer[0] = getTemperature();
    temp_temperature = String(temp_hum_buffer[0]);
    temp_hum_buffer[1] = getHumidity();
    temp_humidity = String(temp_hum_buffer[1]);
    
    delay(1000);
}
#endif