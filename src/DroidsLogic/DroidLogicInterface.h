#pragma once

#include <Arduino.h>


class DroidLogicInterface
{
    public:
        void virtual init() = 0;
        void virtual run() = 0;
    
};