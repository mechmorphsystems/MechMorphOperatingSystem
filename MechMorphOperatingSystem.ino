#pragma once

#include <Arduino.h>
#include "Config.h"

#ifdef DO_DROID
#include "src/DroidsLigic/DO/DOLogic.h"
DOLogic droidLogic;
#endif

#ifdef BR2U_DROID
#include "src/DroidsLigic/BR2U/BR2ULogic.h"
BR2ULogic droidLogic;
#endif

#ifdef MINI_SENTRY_DROID
#include "src/DroidsLigic/MiniSentry/MiniSentryLogic.h"
MiniSentryLogic droidLogic;
#endif

#ifdef MINI_GONK_DROID
#include "src/DroidsLigic/MiniGonk/MiniGonkLogic.h"
MiniGonkLogic droidLogic;
#endif

#ifdef MINI_R2D2_DROID
#include "src/DroidsLigic/MiniR2D2/MiniR2D2Logic.h"
MiniR2D2Logic droidLogic;
#endif

#ifdef MINI_R5D4_DROID
#include "src/DroidsLigic/MiniR2D2/MiniR5D4Logic.h"
MiniR5D4Logic droidLogic;
#endif

#ifdef MINI_MOUSE_DROID
#include "src/DroidsLigic/MiniMouse/MiniMouseLogic.h"
MiniMouseLogic droidLogic;
#endif

#ifdef FERRY_RACER_DROID
#include "src/DroidsLigic/FerryRacer/FerryRacerLogic.h"
FerryRacerLogic droidLogic;
#endif

#ifdef MINI_CH_33P_DROID
#include "src/DroidsLigic/MiniCH33P/MiniCH33PLogic.h"
MiniCH33PLogic droidLogic;
#endif

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
}