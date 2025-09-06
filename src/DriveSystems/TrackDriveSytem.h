#pragma once

#include <Arduino.h>
#include "../Movement/MovementInterface.h"

class TrackDriveSytem
{
    public:
        void init(MovementInterface* motorDriver1, MovementInterface* motorDriver2)
        {
            TrackDriveSytem::motorDriver1 = motorDriver1;
            TrackDriveSytem::motorDriver2 = motorDriver2;
        }
        void run(int16_t yValue, int16_t xValue)
        {
            rawLeft = xValue + yValue;
            rawRight = xValue - yValue;

            diff = abs(abs(xValue) - abs(yValue));
            rawLeft = rawLeft < 0 ? rawLeft - diff : rawLeft + diff;
            rawRight = rawRight < 0 ? rawRight - diff : rawRight + diff;

            rawLeft = constrain(rawLeft, -512, 512);
            rawRight = constrain(rawRight, -512, 512);
            motorDriver1->run(rawRight);
            motorDriver2->run(rawLeft);

        }
    private:
        MovementInterface* motorDriver1;
        MovementInterface* motorDriver2;
        int16_t rawLeft;
        int16_t rawRight;
        int16_t diff;
};
