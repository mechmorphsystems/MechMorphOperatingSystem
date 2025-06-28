#pragma once

#include <Arduino.h>
#include "../../../DroidConfigs/MiniSentryConfig.h"
#include "../DroidLogicInterface.h"
#include "../../Controllers/GamepadController.h"
#include "../../Movement/ImprovedServo.h"
#include "../../Movement/Esc.h"
#include "../../../Config.h"

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
        float yValue;
        float xValue;
        float theta;
        float magnitude;
        float rotation;
        float esc1Speed;
        float esc2Speed;
        float esc3Speed;
        void movement();
};