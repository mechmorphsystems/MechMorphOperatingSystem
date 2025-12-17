#pragma once

#include <Arduino.h>
#include "../../../DroidConfigs/MiniR2D2Config.h"
#include "../DroidLogicInterface.h"
#include "../../Controllers/GamepadController.h"
#include "../../SoundPlayers/DfPlayerMini.h"
#include "../../Movement/ImprovedServo.h"
#include "../../ScriptedAnimation/AnimationRunners/MiniR2D2AnimationRunner.h"
#include "MiniR2D2LightLogic.h"
#include "../../DriveSystems/TrackDriveSytem.h"
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#ifdef ESC_DRIVE
#include "../../Movement/Esc.h"
#endif
#if (defined MX1508_DRIVE || defined MX1508_HEAD)
#include "../../Movement/Driver2Wire.h"
#endif

class MiniR2D2Logic : public DroidLogicInterface
{
    public:
        void init();
        void run();
    private:
        GamepadController controller;
        DfPlayerMini player;
        uint32_t timer = 0;
        #ifdef ESC_DRIVE
        Esc esc1;
        Esc esc2;
        #endif
        #ifdef MX1508_DRIVE
        Driver2Wire drive1;
        Driver2Wire drive2;
        #endif
        #ifdef SERVO_HEAD
        ImprovedServo headServo;
        #endif
        #ifdef MX1508_HEAD
        Driver2Wire headDrive;
        #endif
        ImprovedServo leftArmServo;
        ImprovedServo rightArmServo;
        ImprovedServo shoulderServo;
        ImprovedServo centerLiftServo;
        Adafruit_NeoPixel neoPixelLed = Adafruit_NeoPixel(10, MINI_R2D2_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
        Adafruit_PWMServoDriver servoDriver = Adafruit_PWMServoDriver(0x40);
        MiniR2D2AnimationRunner animationRunnrer;
        MiniR2D2LightLogic lightLogic;
        TrackDriveSytem driveSystem;
        bool holoprojectorStates[3] = {
            false,
            false,
            false
        };
        uint32_t holoprojectorTimers[3] = {
            0,
            0,
            0
        };
        uint16_t holoprojectorIntervals[3] = {
            500,
            600,
            700
        };
        void moveHoloprojector();
};