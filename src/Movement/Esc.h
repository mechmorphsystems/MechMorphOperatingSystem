#pragma once

#include <Arduino.h>
#include "MovementInterface.h"
#include <ESP32Servo.h>
#include "../../Config.h"

class Esc : public MovementInterface
{
    public:
        void setup(
            uint8_t escPin,
            uint16_t centerEscMicrosecons,
            uint16_t minEscMicrosecons,
            uint16_t maxEscMicrosecons,
            bool reverse = false
        ) {
            Esc::escPin = escPin;
            Esc::centerEscMicrosecons = centerEscMicrosecons;
            Esc::minEscMicrosecons = minEscMicrosecons;
            Esc::maxEscMicrosecons = maxEscMicrosecons;
            Esc::reverse = reverse;
        }
        
        void init() override
        {
            esc.attach(escPin);
            esc.writeMicroseconds(centerEscMicrosecons);
        }

        void run(int32_t value) override
        {
            if (reverse) {
                value = -value;
            }
            

            if (value > -STICK_DEADZONE && value < STICK_DEADZONE) {
                esc.writeMicroseconds(centerEscMicrosecons);
            } else if(value < 0) {
                esc.writeMicroseconds(constrain(map(value, -512, 0, minEscMicrosecons, centerEscMicrosecons), minEscMicrosecons, centerEscMicrosecons));
            } else {
                esc.writeMicroseconds(constrain(map(value, 0, 512, centerEscMicrosecons, maxEscMicrosecons), centerEscMicrosecons, maxEscMicrosecons));
            }
        }
    private:
        Servo esc;
        uint8_t escPin = 0;
        uint16_t centerEscMicrosecons = 0;
        uint16_t minEscMicrosecons = 0;
        uint16_t maxEscMicrosecons = 0;
        bool reverse = false;
};
