#pragma once

#include <Arduino.h>
#include "../BaseAnimationRunner.h"
#include "../../../DroidConfigs/MiniCH33PConfig.h"
#include "../../Movement/ImprovedServo.h"

class MiniCH33PAnimationRunner : public BaseAnimationRunner
{
    public:
        void setup(ImprovedServo* armServo)
        {
            MiniCH33PAnimationRunner::armServo = armServo;
        }
        void stop() override
        {
            armServo->writeAngle(MINI_CH_33P_ARM_SERVO_CENTER_ANGLE);

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

                armServo->writeAngle(animation[currenAnimation][animationStep][2]);

                if (animationStep >= animationSteps[currenAnimation]) {
                    stop();
                } else {
                    animationStep++;
                }
            }
        }
    private:
        ImprovedServo* armServo;
        u_int16_t PROGMEM animation[1][4][3] = {
            {
                {0, 0, 0},
                {400, 0, MINI_CH_33P_ARM_SERVO_CENTER_ANGLE},
                {400, 0, 0},
                {400, 0, MINI_CH_33P_ARM_SERVO_CENTER_ANGLE},
            }
        };
        u_int8_t PROGMEM animationSteps[1] = {
            3
        };
};
