#ifndef TEMP_HU_HELPER_H
#define TEMP_HU_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

#include "DHTesp.h"

DHTesp dht;

void tempHuSetup()
{
    MN_DEBUGLN("Temp Setup");
    Serial.begin(115200);
    dht.setup(4, DHTesp::DHT22);
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
#endif