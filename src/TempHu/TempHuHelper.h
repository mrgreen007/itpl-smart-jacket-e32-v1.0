#ifndef TEMP_HU_HELPER_H
#define TEMP_HU_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

#include "DHTesp.h"

DHTesp dht;

void tempHuSetup()
{
    MN_DEBUGLN("Temp Setup");
    dht.setup(TEMP_HUM_PIN, DHTesp::DHT22);
}

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
void tempHuLoop()
{
    current_temperature = getTemperature();
    current_humidity = getHumidity();
    delay(1000);
}
#endif