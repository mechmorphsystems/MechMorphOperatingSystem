#pragma once

#include <Arduino.h>
#include "Config.h"
// #include "src/DroidsLigic/DO/DOLogic.h"
// #include "src/DroidsLigic/BR2U/BR2ULogic.h"
#include "src/DroidsLigic/MiniSentry/MiniSentryLogic.h"

// DOLogic droidLogic;
// BR2ULogic droidLogic;
MiniSentryLogic droidLogic;


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