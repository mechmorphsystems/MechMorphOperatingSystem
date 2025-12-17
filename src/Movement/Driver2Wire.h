#pragma once

#include <Arduino.h>
#include "MovementInterface.h"
#include "../../Config.h"

class Driver2Wire : public MovementInterface
{
    public:
        void setup(
            uint8_t pin1,
            uint8_t pin2,
            int16_t minPwm,
            uint16_t maxPwm,
            bool reverse = false
        ) {
            Driver2Wire::pin1 = pin1;
            Driver2Wire::pin2 = pin2;
            Driver2Wire::minPwm = minPwm;
            Driver2Wire::maxPwm = maxPwm;
            Driver2Wire::reverse = reverse;
        }
        
        void init() override
        {
            pinMode(pin1, OUTPUT);
            pinMode(pin2, OUTPUT);
            digitalWrite(pin1, LOW);
            digitalWrite(pin2, LOW);
        }

        void run(int32_t value) override
        {
            if (reverse) {
                value = -value;
            }

            if (value > -STICK_DEADZONE && value < STICK_DEADZONE) {
                digitalWrite(pin1, LOW);
                digitalWrite(pin2, LOW);
            } else if (value < 0) {
                digitalWrite(pin1, LOW);
                analogWrite(pin2, constrain(map(abs(value), 0, 512, minPwm, maxPwm), minPwm, maxPwm));
            } else {
                analogWrite(pin1, constrain(map(value, 0, 512, minPwm, maxPwm), minPwm, maxPwm));
                digitalWrite(pin2, LOW);
            }
        }
    private:
        uint8_t pin1 = 0;
        uint8_t pin2 = 0;
        int16_t minPwm = 0;
        uint16_t maxPwm = 255;
        bool reverse = false;
};
