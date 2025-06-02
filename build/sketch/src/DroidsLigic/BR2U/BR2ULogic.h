#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/DroidsLigic/BR2U/BR2ULogic.h"
#pragma once

#include <Arduino.h>
#include "../../../DroidConfigs/BR2UConfig.h"
#include "../DroidLogicInterface.h"
#include "../../Controllers/GamepadController.h"
#include "../../SoundPlayers/DfPlayerMini.h"
#include "../../Movement/Esc.h"
#include "../../Movement/ImprovedServo.h"

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
        Esc steeringEsc;
        Esc throttleEsc;
        ImprovedServo headServo;
        ImprovedServo leftHandServo;
        ImprovedServo rightHandServo;
        ImprovedServo canDoorServo;
        ImprovedServo leftCanServo;
        ImprovedServo rightCanServo;
        bool isOpenCanDoor = true;
        bool isLeftCanUp = false;
        bool isRightCanUp = false;
};