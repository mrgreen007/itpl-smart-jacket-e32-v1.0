#ifndef RFID_H
#define RFID_H

#include "config.h"
#include <EasyMFRC522.h>
#include "./Interfaces/BridgeInterface.h"

/**
 * SCK     14
 * MOSI    13
 * MISO    12
 **/

#define BLOCK 1
#define NAME_LEN 40
#define SEC_ID_LEN 8
#define PRI_ID_LEN 4

struct About
{
  byte secID[SEC_ID_LEN];
  char name[NAME_LEN];
  byte accessType;
};

byte priID[PRI_ID_LEN];
byte secID[SEC_ID_LEN];

String rfid_info = "";

//====================================
byte _secID[SEC_ID_LEN] = {0};
String _name = "";
byte _accessType = 0;
//====================================

EasyMFRC522 rfidReader(RFID_SDA_PIN, RFID_RST_PIN);

bool readTag()
{
  About about;

  int result = rfidReader.readRaw(BLOCK, (byte *)&about, sizeof(About));

  if (result >= 0)
  {
    for (int i = 0; i < SEC_ID_LEN; i++)
    {
      secID[i] = about.secID[i];
    }

    char id_2[30];
    sprintf(id_2, "%02X %02X %02X %02X %02X %02X %02X %02X", secID[0], secID[1], secID[2], secID[3], secID[4], secID[5], secID[6], secID[7]);
    MN_DEBUG("   - Sec ID: ");
    MN_DEBUGLN(id_2);
    MN_DEBUG("   - Name: ");
    MN_DEBUGLN(about.name);
    MN_DEBUG("   - Access Type: ");
    MN_DEBUGLN(about.accessType);

    rfid_info = rfid_info + ",\"secondaryid\":\"" + id_2 + "\",\"name\":\"" + about.name + "\",\"accesstype\":\"" + about.accessType + "\"}";
  }
  else
  {
    return false;
  }
  return true;
}

bool writeTag()
{
  About about;

  for (int i = 0; i < SEC_ID_LEN; i++)
  {
    about.secID[i] = _secID[i];
  }

  char name_buff[NAME_LEN];
  _name.toCharArray(name_buff, NAME_LEN);
  strncpy(about.name, name_buff, NAME_LEN - 1);
  about.name[NAME_LEN - 1] = 0;

  about.accessType = _accessType;

  int result = rfidReader.writeRaw(BLOCK, (byte *)&about, sizeof(About));

  if (result < 0)
  {
    return false;
  }
  return true;
}

void rfidSetup()
{
  rfidReader.init();
  delay(100);
  MN_DEBUGLN_F("[OK] RFID setup!");
}

#endif