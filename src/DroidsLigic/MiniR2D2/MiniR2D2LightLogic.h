#pragma once

#include "../../../DroidConfigs/MiniR2D2Config.h"
#include <Adafruit_NeoPixel.h>
#include <Adafruit_PWMServoDriver.h>

class MiniR2D2LightLogic
{
    public:
        void init(Adafruit_NeoPixel* neoPixelLed, Adafruit_PWMServoDriver* servoDriver);
        void runNeopixelLedLight();
        void runRegularLedLight();
    private:
        Adafruit_NeoPixel* neoPixelLed;
        Adafruit_PWMServoDriver* servoDriver;
        bool ledStates[10] = {
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false
        };
        uint32_t ledTimers[10] = {
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0
        };
        uint16_t ledIntervals[10] = {
            500,
            600,
            700,
            800,
            900,
            1000,
            900,
            800,
            700,
            600
        };
        uint8_t neoPixelLedHighLight [10][3] = {
            {255, 255, 255},
            {255, 255, 255},
            {0, 255, 0},
            {0, 0, 0},
            {0, 0, 0},
            {255, 0, 0},
            {0, 0, 0},
            {255, 0, 0},
            {255, 0, 0},
            {255, 0, 0},
        };
        uint8_t neoPixelLedLowLight [10][3] = {
            {0, 0, 255},
            {0, 0, 255},
            {0, 0, 255},
            {0, 0, 0},
            {0, 0, 0},
            {255, 255, 0},
            {0, 0, 0},
            {0, 255, 0},
            {0, 255, 0},
            {0, 255, 0},
        };
};