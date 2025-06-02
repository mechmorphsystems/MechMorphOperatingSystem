#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/Movement/InfinityRorateServo.h"
#pragma once

#include <Arduino.h>
#include "MovementInterface.h"
#include <ESP32Servo.h>
#include "../../Config.h"

class InfinityRorateServo : public MovementInterface
{
    public:
        void setup(
            uint8_t escPin,
            uint16_t centerServoMicrosecons,
            uint16_t minServoMicrosecons,
            uint16_t maxServoMicrosecons,
            bool reverse = false
        ) {
            InfinityRorateServo::escPin = escPin;
            InfinityRorateServo::centerServoMicrosecons = centerServoMicrosecons;
            InfinityRorateServo::minServoMicrosecons = minServoMicrosecons;
            InfinityRorateServo::maxServoMicrosecons = maxServoMicrosecons;
            InfinityRorateServo::reverse = reverse;
        }
        
        void init() override
        {
            servo.attach(escPin);
            servo.writeMicroseconds(centerServoMicrosecons);
        }

        void run(int32_t value) override
        {
            if (reverse) {
                value = -value;
            }
            

            if (value > -STICK_DEADZONE && value < STICK_DEADZONE) {
                servo.writeMicroseconds(centerServoMicrosecons);
            } else if(value < 0) {
                servo.writeMicroseconds(constrain(map(value, -512, 0, minServoMicrosecons, centerServoMicrosecons), minServoMicrosecons, centerServoMicrosecons));
            } else {
                servo.writeMicroseconds(constrain(map(value, 0, 512, centerServoMicrosecons, maxServoMicrosecons), centerServoMicrosecons, maxServoMicrosecons));
            }
        }
    private:
        Servo servo;
        uint8_t escPin = 0;
        uint16_t centerServoMicrosecons = 0;
        uint16_t minServoMicrosecons = 0;
        uint16_t maxServoMicrosecons = 0;
        bool reverse = false;
};
