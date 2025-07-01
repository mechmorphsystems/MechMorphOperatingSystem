#pragma once

#include <Arduino.h>
#include "../BaseAnimationRunner.h"
#include "../../../DroidConfigs/BR2UConfig.h"
#include "../../Movement/ImprovedServo.h"

class BR2UAnimationRunner : public BaseAnimationRunner
{
    public:
        void setup(ImprovedServo* canDoorServo, ImprovedServo* leftCanServo, ImprovedServo* rightCanServo)
        {
            BR2UAnimationRunner::canDoorServo = canDoorServo;
            BR2UAnimationRunner::leftCanServo = leftCanServo;
            BR2UAnimationRunner::rightCanServo = rightCanServo;
        }
        void stop() override
        {
            isRunning = false;
            animationStep = 0;
        }
    protected:
        void runCurrent() override
        {
            if (millis() - timer > animation[currenAnimation][animationStep][3])
            {
                timer = millis();
                canDoorServo->writeAngle(animation[currenAnimation][animationStep][0]);
                leftCanServo->writeAngle(animation[currenAnimation][animationStep][1]);
                rightCanServo->writeAngle(animation[currenAnimation][animationStep][2]);

                if (animationStep >= animationSteps[currenAnimation]) {
                    stop();
                } else {
                    animationStep++;
                }
            }
        }
    private:
        ImprovedServo* canDoorServo;
        ImprovedServo* leftCanServo;
        ImprovedServo* rightCanServo;
        u_int16_t PROGMEM animation[4][3][4] = {
            {
                {0, 90, 90, 0},
                {0, 90, 90, 500},
                {0, 160, 90, 1000},
            },
            {
                {0, 90, 90, 0},
                {0, 90, 90, 500},
                {0, 90, 160, 1000},
            },
            {
                {0, 90, 90, 0},
                {0, 90, 90, 500},
                {0, 160, 160, 1000},
            },
            {
                {0, 90, 90, 0},
                {0, 90, 90, 500},
                {90, 90, 90, 1000},
            }
        };
        u_int8_t PROGMEM animationSteps[4] = {
            2,
            2,
            2,
            2
        };
};
