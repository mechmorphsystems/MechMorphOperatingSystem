#pragma once

#include <Arduino.h>
#include "../Movement/Esc.h"
#include "../Movement/ImprovedServo.h"

class CarDriveSystem
{
    public:
        void init(Esc* throttleEsc, ImprovedServo* steeringServo)
        {
            CarDriveSystem::throttleEsc = throttleEsc;
            CarDriveSystem::steeringServo = steeringServo;
        }
        void run(int16_t throttleValue, int16_t steeringValue)
        {
            throttleEsc->run(throttleValue);
            steeringServo->run(steeringValue);
        }
    private:
        Esc* throttleEsc;
        ImprovedServo* steeringServo;
};