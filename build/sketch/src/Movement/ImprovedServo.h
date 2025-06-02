#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/Movement/ImprovedServo.h"
#pragma once

#include <Arduino.h>
#include "MovementInterface.h"
#include <ESP32Servo.h>
#include "../../Config.h"

class ImprovedServo : public MovementInterface
{
    public:
        void setup(
            uint8_t servoPin,
            uint16_t centerAngle = 90,
            uint16_t angleLimit = 90,
            bool reverse = false
        ) {
            ImprovedServo::servoPin = servoPin;
            ImprovedServo::centerAngle = centerAngle;
            ImprovedServo::angleLimit = angleLimit;
            ImprovedServo::reverse = reverse;
        }
        void init() override
        {
            servo.attach(servoPin);
            servo.write(centerAngle);
            calculateLimits();
        }
        void setMinAngleLimit(uint16_t minAngleLimit)
        {
            ImprovedServo::minAngleLimit = minAngleLimit;
        }
        void setMaxAngleLimit(uint16_t maxAngleLimit)
        {
            ImprovedServo::maxAngleLimit = maxAngleLimit;
            
        }
        void run(int32_t value) override
        {
            if (reverse) {
                value = -value;
            }
            

            if (value > -STICK_DEADZONE && value < STICK_DEADZONE) {
                servo.write(centerAngle);
            } else if(value < 0) {
                servo.write(constrain(map(value, -512, 0, minAngle, centerAngle), minAngle, centerAngle));
            } else {
                servo.write(constrain(map(value, 0, 512, centerAngle, maxAngle), centerAngle, maxAngle));
            }
        }
        void smoothRun(int32_t value)
        {
            value = calculateSmoothValue(value);
            run(value);
        }
        void setSmoothTimeout(uint8_t smoothTimeout = 20)
        {
            ImprovedServo::smoothTimeout = smoothTimeout;
        }
        void writeAngle(uint16_t angle) {
            servo.write(angle);
        }
    private:
        Servo servo;
        uint8_t servoPin = 0;
        uint16_t centerAngle = 90;
        uint16_t angleLimit = 90;
        uint16_t minAngleLimit = 0;
        uint16_t maxAngleLimit = 180;
        uint16_t minAngle = 0;
        uint16_t maxAngle = 180;
        bool reverse = false;
        u_int32_t timer = 0;
        int32_t currentValue = 0;
        uint8_t smoothTimeout = 20;
        int32_t calculateSmoothValue(int32_t value) {
            if (millis() - timer > smoothTimeout)
            {
                timer = millis();

                if (value > -STICK_DEADZONE && value < STICK_DEADZONE) {
                    currentValue = 0;
                } else if (abs(currentValue - value) < 4) {
                    currentValue = value;
                } else if (value < 0) {
                    currentValue-=4;
                } else {
                    currentValue+=4;
                }
            }
            
            return currentValue;
        }
        void calculateLimits()
        {
            minAngle = constrain(centerAngle - angleLimit, minAngleLimit, centerAngle);
            maxAngle = constrain(centerAngle + angleLimit, centerAngle, maxAngleLimit);
        }
};