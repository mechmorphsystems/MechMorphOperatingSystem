#pragma once

#include <Arduino.h>
#include "../BaseAnimationRunner.h"
#include "../../../DroidConfigs/MiniSentryConfig.h"
#include "../../Movement/ImprovedServo.h"

class MiniSentryAnimationRunner : public BaseAnimationRunner
{
    public:
        void setup(ImprovedServo* leftDoorServo, ImprovedServo* rightDoorServo)
        {
            MiniSentryAnimationRunner::leftDoorServo = leftDoorServo;
            MiniSentryAnimationRunner::rightDoorServo = rightDoorServo;
        }
        void stop() override
        {
            leftDoorServo->writeAngle(MINI_SENTRY_LEFT_DOOR_ZERO_ANGLE);
            rightDoorServo->writeAngle(MINI_SENTRY_RIGHT_DOOR_ZERO_ANGLE);
            digitalWrite(LEFT_DOOR_LED_PIN, LOW);
            digitalWrite(RIGHT_DOOR_LED_PIN, LOW);

            isRunning = false;
            animationStep = 0;
        }
    protected:
        void runCurrent() override
        {
            if (millis() - timer > animation[currenAnimation][animationStep][4])
            {
                timer = millis();
                leftDoorServo->writeAngle(animation[currenAnimation][animationStep][0]);
                rightDoorServo->writeAngle(animation[currenAnimation][animationStep][1]);
                digitalWrite(LEFT_DOOR_LED_PIN, animation[currenAnimation][animationStep][2]);
                digitalWrite(RIGHT_DOOR_LED_PIN, animation[currenAnimation][animationStep][3]);

                if (animationStep >= animationSteps[currenAnimation]) {
                    stop();
                } else {
                    animationStep++;
                }
            }
        }
    private:
        ImprovedServo* leftDoorServo;
        ImprovedServo* rightDoorServo;
        u_int16_t PROGMEM animation[1][9][5] = {
            {
                {180, 0, 0, 0, 300},
                {180, 0, 1, 0, 200},
                {180, 0, 0, 1, 200},
                {180, 0, 1, 0, 200},
                {180, 0, 0, 1, 200},
                {180, 0, 1, 0, 200},
                {180, 0, 0, 1, 200},
                {180, 0, 1, 1, 200},
                {MINI_SENTRY_LEFT_DOOR_ZERO_ANGLE, MINI_SENTRY_RIGHT_DOOR_ZERO_ANGLE, 0, 0, 200},
            }
        };
        u_int8_t PROGMEM animationSteps[1] = {
            8
        };
};
