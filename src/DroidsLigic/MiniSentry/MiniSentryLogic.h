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
            MINI_SENTRY_LED_1_PIN,
            MINI_SENTRY_LED_2_PIN,
            MINI_SENTRY_LED_3_PIN,
            MINI_SENTRY_LED_4_PIN,
            MINI_SENTRY_LED_5_PIN,
            MINI_SENTRY_LEFT_DOOR_LED_PIN,
            MINI_SENTRY_RIGHT_DOOR_LED_PIN,
        };
        bool ledStates[5] = {
            false,
            false,
            false,
            false,
            false,
        };
        uint32_t ledTimers[5] = {
            0,
            0,
            0,
            0,
            0,
        };
        uint16_t ledIntervals[5] = {
            500,
            600,
            700,
            800,
            900,
        };
        void movement();
        void ledBlink();
};