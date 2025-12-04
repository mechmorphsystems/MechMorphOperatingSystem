#pragma once

#include <Arduino.h>
#include "../DroidLogicInterface.h"
#include "../../../DroidConfigs/MiniR5D4Config.h"
#include "../../Controllers/GamepadController.h"
#include "../../SoundPlayers/DfPlayerMini.h"
#include "../../Movement/Esc.h"
#include "../../Movement/ImprovedServo.h"
#include "../../DriveSystems/TrackDriveSytem.h"
#include "../../ScriptedAnimation/AnimationRunners/MiniR5D4AnimationRunner.h"

class MiniR5D4Logic : public DroidLogicInterface
{
    public:
        void init();
        void run();
        void runMotor();
    private:
        GamepadController controller;
        DfPlayerMini player;
        Esc esc1;
        Esc esc2;
        ImprovedServo headServo;
        ImprovedServo leftArmServo;
        ImprovedServo rightArmServo;
        ImprovedServo shoulderServo;
        ImprovedServo centerLiftServo;
        TrackDriveSytem driveSystem;
        MiniR5D4AnimationRunner animationRunnrer;
};