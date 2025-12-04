#pragma once

#include <Arduino.h>
#include "../../../DroidConfigs/FerryRacerConfig.h"
#include "../DroidLogicInterface.h"
#include "../../Controllers/GamepadController.h"
#include "../../Movement/Esc.h"
#include "../../Movement/ImprovedServo.h"
#include "../../DriveSystems/CarDriveSystem.h"
#include "../../SoundPlayers/DfPlayerMini.h"

class FerryRacerLogic
{
    public:
        void init();
        void run();
    private:
        GamepadController controller;
        Esc throttleEsc;
        ImprovedServo steeringServo;
        ImprovedServo headServo;
        CarDriveSystem driveSystem;
        DfPlayerMini player;
};
