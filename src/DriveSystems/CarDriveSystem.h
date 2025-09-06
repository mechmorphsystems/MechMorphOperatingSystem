#pragma once

#include <Arduino.h>
#include "../Movement/MovementInterface.h"
#include "../Movement/ImprovedServo.h"

class CarDriveSystem
{
    public:
        void init(MovementInterface* motorDriver, ImprovedServo* steeringServo)
        {
            CarDriveSystem::motorDriver = motorDriver;
            CarDriveSystem::steeringServo = steeringServo;
        }
        void run(int16_t throttleValue, int16_t steeringValue)
        {
            motorDriver->run(throttleValue);
            steeringServo->run(steeringValue);
        }
    private:
        MovementInterface* motorDriver;
        ImprovedServo* steeringServo;
};