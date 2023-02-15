#ifndef TEMP_HU_HELPER_H
#define TEMP_HU_HELPER_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"

#include "DHTesp.h"

DHTesp dht;

void tempHuSetup()
{
    dht.setup(TEMP_HUM_PIN, DHTesp::DHT22);
    MN_DEBUGLN_F("[OK] TempHum setup!");
}

void tempHuLoop()
{
    float t = dht.getTemperature();
    float h = dht.getHumidity();
    while (isnan(t) || isnan(h))
    {
        delay(10);
        t = dht.getTemperature();
        h = dht.getHumidity();
    }

    temp_hum_buffer[0] = t;
    temp_temperature = String(t);
    temp_hum_buffer[1] = h;
    temp_humidity = String(h);

    delay(1000);
}
#endif