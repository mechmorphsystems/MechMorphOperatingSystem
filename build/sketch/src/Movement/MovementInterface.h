#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/Movement/MovementInterface.h"
#pragma once

class MovementInterface
{
    public:
        void virtual init() = 0;
        void virtual run(int32_t value) = 0;
};