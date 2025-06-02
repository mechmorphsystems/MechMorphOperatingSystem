#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/SoundPlayers/SoundPlayerInterface.h"
#pragma once

#include <Arduino.h>


class SoundPlayerInterface
{
    public:
        void virtual init() = 0;
        void virtual playFile(uint8_t fileNumber) = 0;
};