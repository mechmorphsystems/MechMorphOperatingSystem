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
            if (millis() - timer > animation[currenAnimation][animationStep][0])
            {
                timer = millis();
                if (animation[currenAnimation][animationStep][1] > 0 && currentSound != animation[currenAnimation][animationStep][1]) {
                    currentSound = animation[currenAnimation][animationStep][1];
                    player->playFile(animation[currenAnimation][animationStep][1]);
                }

                canDoorServo->writeAngle(animation[currenAnimation][animationStep][2]);
                leftCanServo->writeAngle(animation[currenAnimation][animationStep][3]);
                rightCanServo->writeAngle(animation[currenAnimation][animationStep][4]);

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
        u_int16_t PROGMEM animation[4][3][5] = {
            {
                {0, 0, 0, 90, 90},
                {500, 0, 0, 90, 90},
                {1000, 0, 0, 160, 90},
            },
            {
                {0, 0, 0, 90, 90},
                {500, 0, 0, 90, 90},
                {1000, 0, 0, 90, 160},
            },
            {
                {0, 0, 0, 90, 90},
                {500, 0, 0, 90, 90},
                {1000, 0, 0, 160, 160},
            },
            {
                {0, 0, 0, 90, 90},
                {500, 0, 0, 90, 90},
                {1000, 0, 90, 90, 90},
            }
        };
        u_int8_t PROGMEM animationSteps[4] = {
            2,
            2,
            2,
            2
        };
};
