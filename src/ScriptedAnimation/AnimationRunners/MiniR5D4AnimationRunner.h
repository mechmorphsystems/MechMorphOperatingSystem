
#pragma once

#include <Arduino.h>
#include "../BaseAnimationRunner.h"
#include "../../../DroidConfigs/MiniR2D2Config.h"
#include "../../Movement/ImprovedServo.h"

class MiniR5D4AnimationRunner : public BaseAnimationRunner
{
    public:
        void setup(
            ImprovedServo* leftArmServo,
            ImprovedServo* rightArmServo,
            ImprovedServo* shoulderServo,
            ImprovedServo* centerLiftServo
        ) {
            MiniR5D4AnimationRunner::leftArmServo = leftArmServo;
            MiniR5D4AnimationRunner::rightArmServo = rightArmServo;
            MiniR5D4AnimationRunner::shoulderServo = shoulderServo;
            MiniR5D4AnimationRunner::centerLiftServo = centerLiftServo;
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

                leftArmServo->writeAngle(animation[currenAnimation][animationStep][2]);
                rightArmServo->writeAngle(animation[currenAnimation][animationStep][3]);
                shoulderServo->writeAngle(animation[currenAnimation][animationStep][4]);
                centerLiftServo->writeAngle(animation[currenAnimation][animationStep][5]);

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
        u_int16_t PROGMEM animation[4][4][6] = {
            {
                {0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, 180, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
                {2000, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, 180, 180},
            },
            {
                {0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, 180, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
                {2000, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
            },
            {
                {0, 0, 150, 150, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
                {300, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
                {300, 0, 150, 150, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
                {300, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE},
            },
            {
                {0, 0, 90, 90, 0},
                {0, 0, 90, 90, 500},
                {90, 0, 90, 90, 1000},
            }
        };
        u_int8_t PROGMEM animationSteps[4] = {
            1,
            1,
            3,
            2
        };
};
