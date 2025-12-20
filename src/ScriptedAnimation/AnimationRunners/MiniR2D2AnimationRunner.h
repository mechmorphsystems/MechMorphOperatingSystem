
#pragma once

#include <Arduino.h>
#include "../BaseAnimationRunner.h"
#include "../../../DroidConfigs/MiniR2D2Config.h"
#include "../../Movement/ImprovedServo.h"
#include "../../DriveSystems/TrackDriveSytem.h"
#include <Adafruit_NeoPixel.h>
#include <Adafruit_PWMServoDriver.h>

class MiniR2D2AnimationRunner : public BaseAnimationRunner
{
    public:
        void setup(
            DfPlayerMini* player,
            TrackDriveSytem* driveSytem,
            ImprovedServo* leftArmServo,
            ImprovedServo* rightArmServo,
            ImprovedServo* shoulderServo,
            ImprovedServo* centerLiftServo,
            Adafruit_NeoPixel* neoPixelLed,
            Adafruit_PWMServoDriver* servoDriver
        ) {
            MiniR2D2AnimationRunner::player = player;
            MiniR2D2AnimationRunner::driveSytem = driveSytem;
            MiniR2D2AnimationRunner::leftArmServo = leftArmServo;
            MiniR2D2AnimationRunner::rightArmServo = rightArmServo;
            MiniR2D2AnimationRunner::shoulderServo = shoulderServo;
            MiniR2D2AnimationRunner::centerLiftServo = centerLiftServo;
            MiniR2D2AnimationRunner::neoPixelLed = neoPixelLed;
            MiniR2D2AnimationRunner::servoDriver = servoDriver;
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

                driveSytem->run(animation[currenAnimation][animationStep][2], animation[currenAnimation][animationStep][3]);
                leftArmServo->writeAngle(animation[currenAnimation][animationStep][4]);
                rightArmServo->writeAngle(animation[currenAnimation][animationStep][5]);
                shoulderServo->writeAngle(animation[currenAnimation][animationStep][6]);
                centerLiftServo->writeAngle(animation[currenAnimation][animationStep][7]);
                servoDriver->setPWM(0, 0, animation[currenAnimation][animationStep][8]);
                servoDriver->setPWM(1, 0, animation[currenAnimation][animationStep][9]);
                servoDriver->setPWM(2, 0, animation[currenAnimation][animationStep][10]);
                servoDriver->setPWM(3, 0, animation[currenAnimation][animationStep][11]);
                
                for (uint8_t i = 12; i < 23; i++) {
                    if (0 == animation[currenAnimation][animationStep][i]) {
                        if (12 == i) {
                            servoDriver->setPWM(4, 0, 4096); // low
                        } else {
                            #ifdef NEO_PIXEL_LED
                            neoPixelLed->setPixelColor(i - 13, 0, 0, 0);
                            #endif 

                            #ifdef REGULAR_LED
                            servoDriver->setPWM(i - 8, 0, 4096); // low
                            #endif
                        }
                    }
                    
                    if (1 == animation[currenAnimation][animationStep][i]) {
                        if (12 == i) {
                            servoDriver->setPWM(4, 4096, 0); // high
                        } else {
                            #ifdef NEO_PIXEL_LED
                            neoPixelLed->setPixelColor(
                                i - 13,
                                neoPixelLed->Color(neoPixelLedAnimation[currenAnimation][animationStep][i - 13][0],
                                neoPixelLedAnimation[currenAnimation][animationStep][i - 13][2],
                                neoPixelLedAnimation[currenAnimation][animationStep][i - 13][3])
                            );
                            #endif 

                            #ifdef REGULAR_LED
                            servoDriver->setPWM(i - 8, 4096, 0); // high
                            #endif
                        }
                    }
                }

                #ifdef NEO_PIXEL_LED
                neoPixelLed->show();
                #endif 

                if (animationStep >= animationSteps[currenAnimation]) {
                    stop();
                } else {
                    animationStep++;
                }
            }
        }
    private:
        TrackDriveSytem* driveSytem;
        ImprovedServo* leftArmServo;
        ImprovedServo* rightArmServo;
        ImprovedServo* shoulderServo;
        ImprovedServo* centerLiftServo;
        Adafruit_NeoPixel* neoPixelLed;
        Adafruit_PWMServoDriver* servoDriver;
        u_int16_t PROGMEM animation[4][7][23] = {
            // {     
            //     {delay, sound file, drive y, drive x, left arm, right arm, shoulder sevo, lift servo, holo servo 1, holo servo 2, holo servo 3, periscope servo, periscope light, led1, led2, led3, led4, led5, led6, led7, led8, led9, led10},
            // },
            // 2 legs mode
            {
                {0, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, 180, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_DOWN_PVM, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                {700, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, 180, 180, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_DOWN_PVM, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
            },
            // 3 legs mode
            {
                {0, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, 180, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_DOWN_PVM, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                {700, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_DOWN_PVM, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
            },
            // arm movement
            {
                {0, 0, 0, 0, 150, 150, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_DOWN_PVM, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                {300, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_DOWN_PVM, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                {300, 0, 0, 0, 150, 150, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_DOWN_PVM, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                {300, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_DOWN_PVM, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
            },
            // periscope movement
            {
                {300, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_UP_PVM, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                {200, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_UP_PVM, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                {100, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_UP_PVM, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                {100, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_UP_PVM, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                {100, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_UP_PVM, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                {200, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_UP_PVM, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                {300, 0, 0, 0, MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE, MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE, MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM, MINI_R2D2_PERISCOPE_DOWN_PVM, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
            }
        };
        u_int8_t PROGMEM animationSteps[4] = {
            1,
            1,
            3,
            6
        };
        u_int8_t neoPixelLedAnimation[4][4][10][3] = {};
};
