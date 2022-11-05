#include <Arduino.h>
#include "GPS/GpsHelper.h"
#include "GyroAccelero/GyroAcceleroHelper.h"
#include "Interfaces/BridgeInterface.h"

GPSHelper gpsHelper = GPSHelper();
GyroAcceleroHelper gyroHelper = GyroAcceleroHelper();

// ANKITA
void gpsHandlerTask(void *pvParameters)
{
  (void)pvParameters;
  gpsHelper.setup();

  while (true)
  {
    gpsHelper.loop();
    vTaskDelay(1000 / portTICK_PERIOD_MS); // delay(100);
  }
}

// AAHELI
void gyroAcceleroHandlerTask(void *pvParameters)
{
  (void)pvParameters;
  gyroHelper.setup();

  while (true)
  {
    gyroHelper.loop();
  }
}

// KOUSTAV

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  MN_DEBUGLN("\n\nInitializing...\n\n");

  // Ankita
  xTaskCreate(gpsHandlerTask, "GPS Task", 4 * 1024, NULL, 1, NULL);

  // Aaheli
  xTaskCreate(gyroAcceleroHandlerTask, "GA Task", 4 * 1024, NULL, 1, NULL);

  // Koustav
}

void loop()
{
  digitalWrite(2, !digitalRead(2));
  delay(1000);
}
