#pragma once

#include <Arduino.h>
#include "../DroidLogicInterface.h"
#include "../../../DroidConfigs/MiniCH33PConfig.h"
#include "../../Controllers/GamepadController.h"
#include "../../Movement/Esc.h"
#include "../../Movement/ImprovedServo.h"
#include "../../SoundPlayers/DfPlayerMini.h"
#include "../../DriveSystems/TrackDriveSytem.h"

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
        TrackDriveSytem driveSystem;
};