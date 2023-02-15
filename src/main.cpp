#include "WiFi.h"
#include "GPS/GpsHelper.h"
#include "GyroAccelero/GyroAcceleroHelper.h"
#include "TempHu/TempHuHelper.h"
#include "SoundSensor/SoundSensorHelper.h"
#include "Interfaces/BridgeInterface.h"
#include "Firebase/FirebaseHelper.h"

// :Temporary wifi creds:
// const char *ssid = "LAPTOP-N8V9637C 6288";
// const char *password = "%0T521o8";
const char *ssid = "ANKITA";
const char *password = "an9123314645kita";

String timestamp = "";
String device_id = "";

String getUniqueID()
{
  uint8_t mac_arr[6];
  WiFi.macAddress(mac_arr);
  char _unique_id[13] = {0};
  sprintf(_unique_id, "%02X%02X%02X%02X%02X%02X", mac_arr[0], mac_arr[1], mac_arr[2], mac_arr[3], mac_arr[4], mac_arr[5]);
  return _unique_id;
}

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

void tempHumHandlerTask(void *pvParameters)
{
  (void)pvParameters;
  tempHuSetup();

  while (true)
  {
    tempHuLoop();
  }
}

void soundSensorHandlerTask(void *pvParameters)
{
  (void)pvParameters;
  soundSensorSetup();

  while (true)
  {
    soundSensorLoop();
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  MN_DEBUGLN("\n\n### Initializing...");

  // WiFi setup will be restructed in Phase-3
  MN_DEBUGLN("Connecting to WiFi.");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    MN_DEBUG(".");
  }
  MN_DEBUGLN("\nConnected to the WiFi network!");

  device_id = getUniqueID();
  MN_DEBUG("Device ID: ");
  MN_DEBUGLN(device_id);

  firebaseSetup();

  xTaskCreate(gpsHandlerTask, "GPS Task", 4 * 1024, NULL, 1, NULL);
  xTaskCreate(gyroAcceleroHandlerTask, "GA Task", 4 * 1024, NULL, 1, NULL);
  xTaskCreate(tempHumHandlerTask, "TH Task", 4 * 1024, NULL, 1, NULL);
  xTaskCreate(soundSensorHandlerTask, "SNL Task", 4 * 1024, NULL, 1, NULL);
}

void loop()
{
  if (!gyro_accelero_mutex && !sound_sensor_mutex)
  {
    gps_mutex = false;
    MN_DEBUGLN(">>> buffer full <<<");
    MN_DEBUGLN("[START] Sending data...");
    timestamp = String(start_timestamp);
    timestamp += "-";
    timestamp += String(end_timestamp);
    updateDB(timestamp);
    MN_DEBUGLN("[SUCCESS] Done!");

    gyro_accelero_mutex = true;
    gps_mutex = true;
    sound_sensor_mutex = true;
  }
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  delay(500);
}
