#pragma once

#include <Arduino.h>
#include "../SoundPlayers/DfPlayerMini.h"

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
        DfPlayerMini* player;
        bool isRunning = false;
        uint8_t currenAnimation = 255;
        uint32_t timer = 0;
        uint64_t animationStep = 0;
        u_int16_t PROGMEM animation[1][1][1];
        u_int8_t PROGMEM animationSteps[1];
        u_int16_t currentSound = 0;
        void virtual runCurrent() = 0;
};

