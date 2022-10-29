#include <Arduino.h>
#include "gps_Ankita/gpsHelper.h"
#include "accelero_Koustav/acceleroHelper.h"
#include "gyro_Aaheli/gyroHelper.h"



GPSHelper gpsHelper=GPSHelper();
AcceleroHelper acceleroHelper=AcceleroHelper();
GYROHelper gyroHelper=GYROHelper();

//ANKITA
void gpsHandlerTask(void *pvParameters)
{
  (void)pvParameters;
  gpsHelper.setup();

  while (true)
  {
    gpsHelper.loop();
    vTaskDelay(1000 / portTICK_PERIOD_MS); //delay(100);
  }

    
}

//AAHELI
void gyroHandlerTask(void *pvParameters)
{
  (void)pvParameters;
  gyroHelper.setup();

  while (true)
  {
    gyroHelper.loop();
    vTaskDelay(1500 / portTICK_PERIOD_MS); //delay(100);
  }

    
}

//KOUSTAV
void accelerohandlerTask(void *pvParameters)
{
  (void)pvParameters;
  acceleroHelper.setup();

  while (true)
  {
    acceleroHelper.loop();
    vTaskDelay(2000 / portTICK_PERIOD_MS); //delay(100);
  }

    
}

void setup()
{
  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  MN_DEBUGLN("\n\nInitializing...\n\n");

  // Ankita
  xTaskCreate(gpsHandlerTask, "GPS Handler Task", 4*1024, NULL, 1, NULL);

  // Aaheli
  xTaskCreate(gyroHandlerTask, "Gyroscope Handler Task", 4*1024, NULL, 1, NULL);
  
  // Koustav
  xTaskCreate(accelerohandlerTask, "Accelerometer Handler Task", 4*1024, NULL, 1, NULL);
}

void loop()
{
  //Temporary
  vTaskDelay(100 / portTICK_PERIOD_MS); //delay(100);
}
