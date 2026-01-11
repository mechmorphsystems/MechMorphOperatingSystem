#pragma once

#include <Arduino.h>
#include "../DroidLogicInterface.h"
#include "../../../DroidConfigs/MiniCH33PConfig.h"
#include "../../Controllers/GamepadController.h"
#include "../../Movement/Esc.h"
#include "../../Movement/ImprovedServo.h"
#include "../../SoundPlayers/DfPlayerMini.h"
#include "../../DriveSystems/TrackDriveSytem.h"
#include "../../ScriptedAnimation/AnimationRunners/MiniCH33PAnimationRunner.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class MiniCH33PLogic : public DroidLogicInterface
{
    public:
        void init();
        void run();
    private:
        GamepadController controller;
        DfPlayerMini player;
        Esc esc1;
        Esc esc2;
        ImprovedServo headServo;
        ImprovedServo armServo;
        TrackDriveSytem driveSystem;
        MiniCH33PAnimationRunner animationRunner;
        Adafruit_PWMServoDriver servoDriver = Adafruit_PWMServoDriver(0x40);
        uint8_t frontLogicState = 0;
        int8_t frontLogicPointer = 0;
        uint8_t frontLogicRandomPointer = 0;
        uint32_t frontLogicTimer = 0;
        bool rearLogicStates[4] = {
            false,
            false,
            false,
            false,
        };
        uint32_t rearLogicTimers[4] = {
            0,
            0,
            0,
            0,
        };
        uint16_t rearLogicIntervals[4] = {
            500,
            600,
            700,
            800,
        };
        void frontLogicLight();
        void rearLogicLight();
};