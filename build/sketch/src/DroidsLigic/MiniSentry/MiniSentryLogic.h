#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/DroidsLigic/MiniSentry/MiniSentryLogic.h"
#pragma once

#include <Arduino.h>
#include "../../../DroidConfigs/MiniSentryConfig.h"
#include "../DroidLogicInterface.h"
#include "../../Controllers/GamepadController.h"
#include "../../Movement/ImprovedServo.h"
#include "../../Movement/Esc.h"

class MiniSentryLogic : public DroidLogicInterface
{
    public:
        void init();
        void run();
    private:
        GamepadController controller;
        uint32_t timer = 0;
        ImprovedServo leftDoorServo;
        ImprovedServo rightDoorServo;
        Esc esc1;
        Esc esc2;
        Esc esc3;
};