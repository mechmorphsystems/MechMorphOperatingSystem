#pragma once

#include <Arduino.h>
#include "MovementInterface.h"
#include <GyverMotor.h>
#include "../../Config.h"

class Driver2Wire : public MovementInterface
{
    public:
        void setup(
            uint8_t pin1,
            uint8_t pin2,
            uint8_t minDuty,
            int16_t minLimit,
            uint16_t maxLimit,
            bool reverse = false
        ) {
            Driver2Wire::pin1 = pin1;
            Driver2Wire::pin2 = pin2;
            Driver2Wire::minDuty = minDuty;
            Driver2Wire::minLimit = minLimit;
            Driver2Wire::maxLimit = maxLimit;
            Driver2Wire::reverse = reverse;
        }
        
        void init() override
        {
            motor = GMotor(DRIVER2WIRE, pin1, pin2);
            motor.setMinDuty(minDuty);
        }

        void run(int32_t value) override
        {
            if (reverse) {
                value = -value;
            }
            

            if (value > -STICK_DEADZONE && value < STICK_DEADZONE) {
                motor.setSpeed(0);
            } else {
                motor.setSpeed(constrain(map(value, -255, 255, minLimit, maxLimit), minLimit, maxLimit));
            }
        }
    private:
        GMotor motor = GMotor(DRIVER2WIRE, pin1, pin2);
        uint8_t pin1;
        uint8_t pin2;
        uint8_t minDuty;
        int16_t minLimit = -255;
        uint16_t maxLimit = 255;
        bool reverse = false;
};
