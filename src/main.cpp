#include "WiFi.h"
#include "GPS/GpsHelper.h"
#include "GyroAccelero/GyroAcceleroHelper.h"
#include "Interfaces/BridgeInterface.h"
#include "Firebase/FirebaseHelper.h"

const char *ssid = "Aaheli_Phone";
const char *password = "y235utvs";
String timestamp = "";

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

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    MN_DEBUGLN("Connecting to WiFi..");
  }

  MN_DEBUGLN("Connected to the WiFi network");

  firebaseSetup();

  xTaskCreate(gpsHandlerTask, "GPS Task", 4 * 1024, NULL, 1, NULL);

  xTaskCreate(gyroAcceleroHandlerTask, "GA Task", 4 * 1024, NULL, 1, NULL);
}

void loop()
{
  if (gyro_accelero_mutex == false) // && gps_mutex == false
  {
    MN_DEBUGLN(">>> buffer full <<<");

    MN_DEBUGLN("[START] Sending data...");
    timestamp = String(start_timestamp);
    timestamp += "-";
    timestamp += String(end_timestamp);
    updateDB(timestamp);
    MN_DEBUGLN("[SUCCESS] Done!");

    gyro_accelero_mutex = true;
    // gps_mutex = true;
  }
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  delay(500);
}
