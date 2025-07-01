#pragma once

#include <Arduino.h>
#include "../../../DroidConfigs/BR2UConfig.h"
#include "../DroidLogicInterface.h"
#include "../../Controllers/GamepadController.h"
#include "../../SoundPlayers/DfPlayerMini.h"
#include "../../Movement/Esc.h"
#include "../../Movement/ImprovedServo.h"
#include "../../ScriptedAnimation/AnimationRunners/BR2UAnimationRunner.h"

class BR2ULogic : public DroidLogicInterface
{
    public:
        void init();
        void run();
        void runMotor();
        void canMotion();
    private:
        GamepadController controller;
        DfPlayerMini player;
        uint32_t timer = 0;
        Esc esc1;
        Esc esc2;
        ImprovedServo headServo;
        ImprovedServo leftHandServo;
        ImprovedServo rightHandServo;
        ImprovedServo canDoorServo;
        ImprovedServo leftCanServo;
        ImprovedServo rightCanServo;
        BR2UAnimationRunner animationRunnrer;
        int16_t yValue;
        int16_t xValue;
        int16_t rawLeft;
        int16_t rawRight;
        int16_t diff;
};