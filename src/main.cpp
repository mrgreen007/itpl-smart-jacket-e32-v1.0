#include "GPS/GpsHelper.h"
#include "GyroAccelero/GyroAcceleroHelper.h"
#include "Interfaces/BridgeInterface.h"

void gpsHandlerTask(void *pvParameters)
{
  (void)pvParameters;
  gpsSetup();

  while (true)
  {
    gpsLoop();
  }
}

void gyroAcceleroHandlerTask(void *pvParameters)
{
  (void)pvParameters;
  gyroAcceleroSetup();

  while (true)
  {
    gyroAcceleroLoop();
  }
}

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
}

void loop()
{
  if(gyro_accelero_mutex == false && gps_mutex == false)
  {
    // MN_DEBUGLN("> buffer full <");
    // delay(5*1000);
    // gyro_accelero_mutex = true;
    // gps_mutex = true;
  }
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  delay(500);
}
