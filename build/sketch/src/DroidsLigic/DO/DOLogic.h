#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/DroidsLigic/DO/DOLogic.h"
#pragma once

#include <Arduino.h>
#include "../../../DroidConfigs/DOConfig.h"
#include "../DroidLogicInterface.h"
#include "../../Controllers/GamepadController.h"
#include "../../SoundPlayers/DfPlayerMini.h"
#include "DOBodyMovement.h"
#include "DoHeadMovement.h"
// #include <ESP32Servo.h>
// #include "../../DriveMotors/Esc.h"

class DOLogic : public DroidLogicInterface
{
    public:
        void init();
        void run();
    private:
        GamepadController controller;
        DfPlayerMini player;
        DOBodyMovement doBodyMovement;
        DoHeadMovement doHeadMovement;
        uint32_t timer = 0;
        Servo servo1;
        // Servo servo2;
        // Esc esc1;
        // Esc esc2;
};