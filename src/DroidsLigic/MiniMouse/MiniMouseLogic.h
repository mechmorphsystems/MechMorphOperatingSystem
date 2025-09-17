#pragma once

#include <Arduino.h>
#include "../DroidLogicInterface.h"
#include "../../../DroidConfigs/MiniMouseConfig.h"
#include "../../Controllers/GamepadController.h"
#include "../../Movement/Esc.h"
#include "../../SoundPlayers/DfPlayerMini.h"
#include "../../Movement/ImprovedServo.h"
#include "../../DriveSystems/CarDriveSystem.h"

class MiniMouseLogic : public DroidLogicInterface
{
    public:
        void init();
        void run();
    private:
        GamepadController controller;
        Esc esc;
        ImprovedServo servo;
        DfPlayerMini player;
        CarDriveSystem driveSystem;
};