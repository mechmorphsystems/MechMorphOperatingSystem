#pragma once

#include <Arduino.h>
#include "../../../DroidConfigs/MiniSentryConfig.h"
#include "../DroidLogicInterface.h"
#include "../../Controllers/GamepadController.h"
#include "../../Movement/ImprovedServo.h"
#include "../../Movement/Esc.h"
#include "../../../Config.h"
#include "../../ScriptedAnimation/AnimationRunners/MiniSentryAnimationRunner.h"

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
        MiniSentryAnimationRunner animationRunnrer;
        float yValue;
        float xValue;
        float theta;
        float magnitude;
        float rotation;
        float esc1Speed;
        float esc2Speed;
        float esc3Speed;
        uint32_t ledTimer = 0;
        uint8_t ledPosition = 0;
        uint8_t PROGMEM leds[7] = {
            LED_1_PIN,
            LED_2_PIN,
            LED_3_PIN,
            LED_4_PIN,
            LED_5_PIN,
            LEFT_DOOR_LED_PIN,
            RIGHT_DOOR_LED_PIN
        };
        void movement();
        void ledBlink();
};