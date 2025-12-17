#pragma once

#include <Arduino.h>
#include "../../../DroidConfigs/MiniR2D2Config.h"
#include "../DroidLogicInterface.h"
#include "../../Controllers/GamepadController.h"
#include "../../SoundPlayers/DfPlayerMini.h"
#include "../../Movement/Esc.h"
#include "../../Movement/ImprovedServo.h"
#include "../../ScriptedAnimation/AnimationRunners/MiniR2D2AnimationRunner.h"
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "MiniR2D2LightLogic.h"
#include "../../DriveSystems/TrackDriveSytem.h"

class MiniR2D2Logic : public DroidLogicInterface
{
    public:
        void init();
        void run();
    private:
        GamepadController controller;
        DfPlayerMini player;
        uint32_t timer = 0;
        Esc esc1;
        Esc esc2;
        ImprovedServo headServo;
        ImprovedServo leftArmServo;
        ImprovedServo rightArmServo;
        ImprovedServo shoulderServo;
        ImprovedServo centerLiftServo;
        MiniR2D2AnimationRunner animationRunnrer;
        Adafruit_NeoPixel pixel = Adafruit_NeoPixel(10, MINI_R2D2_NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
        Adafruit_PWMServoDriver servoDriver = Adafruit_PWMServoDriver(0x40);
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
        bool state = true;
};