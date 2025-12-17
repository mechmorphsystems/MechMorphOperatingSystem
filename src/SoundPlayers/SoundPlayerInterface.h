#pragma once

#include <Arduino.h>


class SoundPlayerInterface
{
    public:
        void virtual init() = 0;
        void virtual playFile(uint16_t fileNumber) = 0;
};