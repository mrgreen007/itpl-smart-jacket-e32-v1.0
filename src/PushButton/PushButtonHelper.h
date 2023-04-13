#include "./Interfaces/BridgeInterface.h"
#include "RFID/RfidHelper.h"
#include "Buzzer/BuzzerHelper.h"
#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H
#include "config.h"
#include <OneButton.h>

unsigned long start_time;

OneButton button(PUSH_BUTTON_GPIO_PIN, true); // false - will read 1(pull down) on pressing button; true - will read 0 (pull up)

void tripleClick()
{
    led_mutex = false;
    MN_DEBUGLN("Triple Click");
    start_time = millis();
    while (millis() - start_time < 30000)
    {
        bool success = false;
        success = rfidReader.detectTag(priID);
        if (success)
        {
            char buff[60];
            sprintf(buff, "%02X%02X%02X%02X", priID[0], priID[1], priID[2], priID[3]);
            rfidReader.unselectMifareTag();
            rfid_id_tag = buff;
            MN_DEBUGLN("rfid_id_tag");
            MN_DEBUGLN(rfid_id_tag);
            alertType=once;
            break;
        }
        // delay(10);
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        delay(100);
    }
    // MN_DEBUGLN("30 sec up");
    led_mutex = true;
}

void singleClick()
{
    MN_DEBUGLN("Click");
}

void longClick()
{
    MN_DEBUGLN("Long Click");
}

void pushButtonSetup()
{
    pinMode(PUSH_BUTTON_GPIO_PIN, INPUT);
    button.attachTripleClick(tripleClick); // link the function to be called on a doubleclick event.
    button.attachLongPressStop(longClick); // link the function to be called on a longpress event.
    MN_DEBUGLN_F("[OK] Push Button setup!");
}

void pushButtonLoop()
{
    if (push_button_mutex)
    {
        button.tick(); // check the status of the button
        delay(10);     // a short wait between checking the button
    }
    else
    {
        delay(10);
    }
}
#endif