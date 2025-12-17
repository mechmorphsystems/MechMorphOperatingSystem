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
            digitalWrite(MINI_SENTRY_LEFT_DOOR_LED_PIN, LOW);
            digitalWrite(MINI_SENTRY_RIGHT_DOOR_LED_PIN, LOW);

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

                leftDoorServo->writeAngle(animation[currenAnimation][animationStep][2]);
                rightDoorServo->writeAngle(animation[currenAnimation][animationStep][3]);
                digitalWrite(MINI_SENTRY_LEFT_DOOR_LED_PIN, animation[currenAnimation][animationStep][4]);
                digitalWrite(MINI_SENTRY_RIGHT_DOOR_LED_PIN, animation[currenAnimation][animationStep][5]);

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
        u_int16_t PROGMEM animation[1][9][6] = {
            {
                {300, 0, 180, 0, 0, 0},
                {200, 0, 180, 0, 1, 0},
                {200, 0, 180, 0, 0, 1},
                {200, 0, 180, 0, 1, 0},
                {200, 0, 180, 0, 0, 1},
                {200, 0, 180, 0, 1, 0},
                {200, 0, 180, 0, 0, 1},
                {200, 0, 180, 0, 1, 1},
                {200, 0, MINI_SENTRY_LEFT_DOOR_ZERO_ANGLE, MINI_SENTRY_RIGHT_DOOR_ZERO_ANGLE, 0, 0},
            }
        };
        u_int8_t PROGMEM animationSteps[1] = {
            8
        };
};
