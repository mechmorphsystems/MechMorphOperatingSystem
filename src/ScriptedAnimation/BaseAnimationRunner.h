#pragma once

#include <Arduino.h>

class BaseAnimationRunner
{
    public:
        void run(uint8_t anumationNumber)
        {
            if (isRunning && currenAnimation != anumationNumber) {
                stop();
            }
            currenAnimation = anumationNumber;
            isRunning = true;

            runCurrent();
        }
        void virtual stop() = 0;
        bool isRunnung(uint8_t anumationNumber)
        {
            return isRunning && anumationNumber == currenAnimation;
        }
    protected:
        bool isRunning = false;
        uint8_t currenAnimation = 255;
        uint32_t timer = 0;
        uint64_t animationStep = 0;
        void virtual runCurrent() = 0;
};

