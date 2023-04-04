#ifndef BUZZER_H
#define BUZZER_H
#include "Buzzer/pitches.h"
#include "config.h"

enum buzzTypes{stop, continuos ,once ,danger ,interval ,tone1 ,tone2 ,tone3 ,tone4} alertType;

void stopBuzzer()
{
    alertType = stop;
    digitalWrite(BUZZER_PIN, LOW);
}

void beepContinuos()
{
    digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));
    delay(800);
}

void beepOnce()
{
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    stopBuzzer();
}

void beepDanger()
{
    for (int i = 700; i < 800; i++)
    {
        tone(BUZZER_PIN, i);
        delay(20);
        MN_DEBUGLN(i);
    }
    for (int i = 800; i > 700; i--)
    {
        tone(BUZZER_PIN, i);
        delay(20);
        MN_DEBUGLN(i);
    }
    noTone(BUZZER_PIN);
    stopBuzzer();
}

void beep(int dur, int interval)
{
    for (int i = 1; i <= round((double)dur / (double)interval); i++)
    {
        digitalWrite(BUZZER_PIN,!digitalRead(BUZZER_PIN));
        delay(interval);
    }
    stopBuzzer();
}

void beepTone1()
{
    int melody[] = {// tone array
                    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0,
                    NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_G3,
                    NOTE_B3, NOTE_B3, NOTE_B3, NOTE_B3, NOTE_A3, NOTE_G3,
                    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_G3, 0};
    int noteDurations[] = {4, 8, 8, 4, 4, 4, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4, 4, 4, 8, 8, 4, 4};
    for (int thisNote = 0; thisNote < 23; thisNote++)
    {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(BUZZER_PIN, melody[thisNote], noteDuration); // play tone
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes); // delay
        noTone(BUZZER_PIN);  // tone off
    }
    stopBuzzer();
}

void beepTone2()
{
    int melody2[] = {NOTE_GS7, NOTE_DS8, NOTE_GS7, 0, NOTE_DS8, NOTE_DS8, 0, NOTE_GS7, NOTE_GS7};
    int noteDurations[] = {4, 8, 8, 4, 8, 8, 4, 4, 4};
    for (int thisNote = 0; thisNote < 9; thisNote++)
    {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(BUZZER_PIN, melody2[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(BUZZER_PIN);
    }
    stopBuzzer();
}

void beepTone3()
{
    int melody3[] = {NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6, NOTE_C7,
                     NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7};
    int noteDurations[] = {4, 8, 8, 4, 8, 8, 4, 4, 4};
    for (int thisNote = 0; thisNote < 9; thisNote++)
    {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(BUZZER_PIN, melody3[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(BUZZER_PIN);
    }
    stopBuzzer();
}

void beepTone4()
{
    int melody4[] = {NOTE_F5, NOTE_C6, NOTE_AS5, NOTE_C6, NOTE_AS5, NOTE_C6, NOTE_GS5,
                     NOTE_AS5, NOTE_C6, NOTE_AS5, NOTE_GS5, NOTE_FS5, NOTE_F5, NOTE_C6,
                     NOTE_AS5, NOTE_C6, NOTE_AS5, NOTE_C6, NOTE_GS5, NOTE_AS5, NOTE_C6,
                     NOTE_AS5, NOTE_F5, NOTE_C6, NOTE_AS5, NOTE_C6, NOTE_AS5, NOTE_C6,
                     NOTE_GS5, NOTE_AS5, NOTE_C6, NOTE_AS5, NOTE_GS5, NOTE_FS5, NOTE_DS5,
                     NOTE_F5, NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_FS5, NOTE_F5};
    int noteDurations[] = {4, 8, 4, 8, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 4, 8, 8, 8, 4, 8, 8, 2, 4, 8, 4, 8, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 2};
    for (int thisNote = 0; thisNote < 43; thisNote++)
    {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(BUZZER_PIN, melody4[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(BUZZER_PIN);
    }
    stopBuzzer();
}

void buzzerSetup()
{
    pinMode(BUZZER_PIN, OUTPUT);
    MN_DEBUGLN_F("[OK] Buzzer sensor setup!");
}

void buzzerLoop()
{
    if (buzzer_mutex)
    {
        switch (alertType)
        {
        case continuos:
            beepContinuos();
            break;
        case once:
            beepOnce();
            break;
        case danger:
            beepDanger();
            break;
        case interval:
            beep(5000,100);
            break;            
        case tone1:
            beepTone1();
            break;
        case tone2:
            beepTone2();
            break;
        case tone3:
            beepTone3();
            break;
        case tone4:
            beepTone4();
            break;
        default:
            delay(100);
        }
    }
    else
    {
        delay(100);
    }
}
#endif