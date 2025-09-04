#pragma once

#include <Arduino.h>
#include "../Movement/Esc.h"

class TrackDriveSytem
{
    public:
        void init(Esc* esc1, Esc* esc2)
        {
            TrackDriveSytem::esc1 = esc1;
            TrackDriveSytem::esc2 = esc2;
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
            esc1->run(rawRight);
            esc2->run(rawLeft);

        }
    private:
        Esc* esc1;
        Esc* esc2;
        int16_t rawLeft;
        int16_t rawRight;
        int16_t diff;
};
