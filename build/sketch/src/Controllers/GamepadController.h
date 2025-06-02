#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/Controllers/GamepadController.h"
#pragma once

#include <Arduino.h>
#include <Bluepad32.h>
#include "../../Config.h"

#define D_PAD_COUNT 4
#define BUTTONS_COUNT 8

class GamepadController
{
    public:
        void init();
        void update();

        bool dPadUpClick();
        bool dPadDownClick();
        bool dPadLeftClick();
        bool dPadRightClick();
        bool croossButtonClick();
        bool squareButtonClick();
        bool triangleButtonClick();
        bool circleButtonClick();
        bool l1ButtonClick();
        bool l3ButtonClick();
        bool r1ButtonClick();
        bool r3ButtonClick();

        bool dPadUpHold();
        bool dPadDownHold();
        bool dPadLeftHold();
        bool dPadRightHold();
        bool croossButtonHold();
        bool squareButtonHold();
        bool triangleButtonHold();
        bool circleButtonHold();
        bool l1ButtonHold();
        bool l3ButtonHold();
        bool r1ButtonHold();
        bool r3ButtonHold();

        int32_t getLeftX();
        int32_t getLeftY();
        int32_t getRightX();
        int32_t getRightY();
        int32_t getBrake();
        int32_t getThrottle();
        int32_t getBrakeThrottleMixed();

        void blinkGreen();
    private:
        ControllerPtr controllerPtr;

        enum {D_PAD, BUTTONS} buttonTypes;
        enum {D_PAD_UP, D_PAD_DOWN, D_PAD_LEFT, D_PAD_RIGHT} dPadMap;
        enum {CROSS, SQUARE, TRIANGLE, CIRCLE, L1, L3, R1, R3} buttonsMap;
        enum {RED, GREEN, BLUE} colorMap;

        uint16_t buttonCodes[2][8] = {
            {
                DPAD_UP, // d-pad up
                DPAD_DOWN, // d-pad down
                DPAD_LEFT, // d-pad left
                DPAD_RIGHT  // d-pad right
            },
            {
                BUTTON_A, // cross
                BUTTON_X, // square
                BUTTON_Y, // triangle
                BUTTON_B, // circle
                BUTTON_SHOULDER_L, // L1
                BUTTON_THUMB_L, // L3
                BUTTON_SHOULDER_R, // R1
                BUTTON_THUMB_R  // R3
            }
        };
        bool buttonFlags[2][8] = {
            {
                false, // d-pad up
                false, // d-pad down
                false, // d-pad left
                false  // d-pad right
            },
            {
                false, // cross
                false, // square
                false, // triangle
                false, // circle
                false, // L1
                false, // L3
                false, // R1
                false  // R3
            },
        };
        bool buttonClics[2][8] = {
            {
                false, // d-pad up
                false, // d-pad down
                false, // d-pad left
                false  // d-pad right
            },
            {
                false, // cross
                false, // square
                false, // triangle
                false, // circle
                false, // L1
                false, // L3
                false, // R1
                false  // R3
            },
        };
        bool buttonHoldFlags[2][8] = {
            {
                false, // d-pad up
                false, // d-pad down
                false, // d-pad left
                false  // d-pad right
            },
            {
                false, // cross
                false, // square
                false, // triangle
                false, // circle
                false, // L1
                false, // L3
                false, // R1
                false  // R3
            },
        };
        uint32_t buttonsHoldTimeout[2][8] = {
            {
                0, // d-pad up
                0, // d-pad down
                0, // d-pad left
                0  // d-pad right
            },
            {
                0, // cross
                0, // square
                0, // triangle
                0, // circle
                0, // L1
                0, // L3
                0, // R1
                0  // R3
            },
        };
        bool buttonHolds[2][8] = {
            {
                false, // d-pad up
                false, // d-pad down
                false, // d-pad left
                false,  // d-pad right
                false,
                false,
                false,
                false
            },
            {
                false, // cross
                false, // square
                false, // triangle
                false, // circle
                false, // L1
                false, // L3
                false, // R1
                false  // R3
            },
        };
        uint8_t colorState = 0;
        void tick(uint8_t buttonType);
        void setRedColorLed();
        void setGreenColorLed();
        void setBlueColorLed();
        void changeColorLedIfAnyButtonHold();
};
