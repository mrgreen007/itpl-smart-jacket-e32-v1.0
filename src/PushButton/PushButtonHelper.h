#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include "config.h"
#include "./Interfaces/BridgeInterface.h"
#include "RFID/RfidHelper.h"
#include "Buzzer/BuzzerHelper.h"
#include <OneButton.h>

unsigned long start_time;

OneButton button(PUSH_BUTTON_PIN, true); // false - will read 1(pull down) on pressing button; true - will read 0 (pull up)

void handleTripleClick()
{
    led_mutex = false;
    MN_DEBUGLN("Triple Click");
    start_time = millis();
    while (millis() - start_time < 30*1000 && !assignTagID())
    {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        delay(100);
    }
    MN_DEBUGLN("[STOP] RFID reading stopped!");
    led_mutex = true;
}

void handleLongPress()
{
    MN_DEBUGLN("Long Click");
}

void pushButtonSetup()
{
    pinMode(PUSH_BUTTON_PIN, INPUT);
    button.attachTripleClick(handleTripleClick); // link the function to be called on a doubleclick event.
    button.attachLongPressStop(handleLongPress); // link the function to be called on a longpress event.
    MN_DEBUGLN_F("[OK] Push Button setup!");
}

void pushButtonLoop()
{
    button.tick(); // check the status of the button
    delay(50);     // a short wait between checking the button
}
#endif