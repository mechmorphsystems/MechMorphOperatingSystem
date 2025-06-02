#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/MechMorphOperatingSystem.ino"
#pragma once

#include <Arduino.h>
#include "Config.h"
// #include "src/DroidsLigic/DO/DOLogic.h"
// #include "src/DroidsLigic/BR2U/BR2ULogic.h"
#include "src/DroidsLigic/MiniSentry/MiniSentryLogic.h"

// DOLogic droidLogic;
// BR2ULogic droidLogic;
MiniSentryLogic droidLogic;


#line 14 "/home/vasya/arduino/MechMorphOperatingSystem/MechMorphOperatingSystem.ino"
void setup();
#line 23 "/home/vasya/arduino/MechMorphOperatingSystem/MechMorphOperatingSystem.ino"
void loop();
#line 14 "/home/vasya/arduino/MechMorphOperatingSystem/MechMorphOperatingSystem.ino"
void setup()
{
    #ifdef DEBUG
        Serial.begin(115200);
    #endif
    
    droidLogic.init();
}

void loop()
{
    droidLogic.run();

    // vTaskDelay(1);
}
