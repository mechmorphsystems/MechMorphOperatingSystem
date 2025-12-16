
#pragma once

#include <Arduino.h>
#include "../BaseAnimationRunner.h"
#include "../../../DroidConfigs/MiniR2D2Config.h"
#include "../../Movement/ImprovedServo.h"

class MiniR2D2AnimationRunner : public BaseAnimationRunner
{
    public:
        void setup(
            ImprovedServo* leftArmServo,
            ImprovedServo* rightArmServo,
            ImprovedServo* shoulderServo,
            ImprovedServo* centerLiftServo
        ) {
            MiniR2D2AnimationRunner::leftArmServo = leftArmServo;
            MiniR2D2AnimationRunner::rightArmServo = rightArmServo;
            MiniR2D2AnimationRunner::shoulderServo = shoulderServo;
            MiniR2D2AnimationRunner::centerLiftServo = centerLiftServo;
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
                leftArmServo->writeAngle(animation[currenAnimation][animationStep][1]);
                rightArmServo->writeAngle(animation[currenAnimation][animationStep][2]);
                shoulderServo->writeAngle(animation[currenAnimation][animationStep][3]);
                centerLiftServo->writeAngle(animation[currenAnimation][animationStep][4]);

                if (animationStep >= animationSteps[currenAnimation]) {
                    stop();
                } else {
                    animationStep++;
                }
            }
        }
    private:
        ImprovedServo* leftArmServo;
        ImprovedServo* rightArmServo;
        ImprovedServo* shoulderServo;
        ImprovedServo* centerLiftServo;
        u_int16_t PROGMEM animation[4][4][5] = {
            {
                {0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, 180, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
                {2000, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, 180, 180},
            },
            {
                {0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, 180, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
                {2000, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
            },
            {
                {0, 150, 150, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
                {300, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
                {300, 150, 150, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
                {300, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
            },
            {
                {0, 90, 90, 0},
                {0, 90, 90, 500},
                {90, 90, 90, 1000},
            }
        };
        u_int8_t PROGMEM animationSteps[4] = {
            1,
            1,
            3,
            2
        };
};
