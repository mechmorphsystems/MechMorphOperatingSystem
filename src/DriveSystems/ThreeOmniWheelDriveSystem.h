#pragma once

#include <Arduino.h>
#include "../../Config.h"
#include "../Movement/MovementInterface.h"

class ThreeOmniWheelDriveSystem
{
    public:
        void init(MovementInterface* motorDriver1, MovementInterface* motorDriver2, MovementInterface* motorDriver3)
        {
            ThreeOmniWheelDriveSystem::motorDriver1 = motorDriver1;
            ThreeOmniWheelDriveSystem::motorDriver2 = motorDriver2;
            ThreeOmniWheelDriveSystem::motorDriver3 = motorDriver3;
        }
        void run(int16_t yValue, int16_t xValue, int16_t rotation)
        {
            theta = atan2(yValue, xValue);
            magnitude = sqrt((yValue * yValue) + (xValue * xValue));

            if (magnitude > 75.0f || rotation > STICK_DEADZONE || rotation < -STICK_DEADZONE) { // the f is a float number to check against i.e. 1/3 = 0.33333
                float vx = magnitude * cos(theta);
                float vy = magnitude * sin(theta);
                const float sqrt3o2 = 1.0 * sqrt(3) / 2;

                //Find wheel vecotrs and do math stuff/////////////////////////////////////////////////////////
                esc1Speed = -vx;                     // v dot [-1, 0] / 25mm               // the 25mm represents the radius of the omniwheel to calculate the angular velocity
                esc2Speed = 0.5 * vx - sqrt3o2 * vy; // v dot [1/2, -sqrt(3)/2] / 25mm
                esc3Speed = 0.5 * vx + sqrt3o2 * vy; // v dot [1/2, +sqrt(3)/2] / 25mm

                esc1Speed = constrain(esc1Speed + rotation, -512, 512);
                esc2Speed = constrain(esc2Speed + rotation, -512, 512);
                esc3Speed = constrain(esc3Speed + rotation, -512, 512);
            }
            else {
                esc1Speed = esc2Speed = esc3Speed = 0;
            }

            motorDriver1->run(esc1Speed);
            motorDriver2->run(esc2Speed);
            motorDriver3->run(esc3Speed);

        }
    private:
        MovementInterface* motorDriver1;
        MovementInterface* motorDriver2;
        MovementInterface* motorDriver3;
        float theta;
        float magnitude;
        float esc1Speed;
        float esc2Speed;
        float esc3Speed;
};