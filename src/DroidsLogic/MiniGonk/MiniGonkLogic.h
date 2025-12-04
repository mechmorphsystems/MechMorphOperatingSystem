#pragma once

#include <Arduino.h>
#include "../../../DroidConfigs/MiniGonkConfig.h"
#include "../DroidLogicInterface.h"
#include "../../Controllers/GamepadController.h"
#include "../../Movement/Esc.h"
#include "../../SoundPlayers/DfPlayerMini.h"

class MiniGonkLogic : public DroidLogicInterface
{
    public:
        void init();
        void run();
    private:
        GamepadController controller;
        uint32_t timer = 0;
        Esc leftEsc;
        Esc rightEsc;
        DfPlayerMini player;
        uint8_t currentState;
        uint8_t nextState;
        bool stateChange = false;
        enum {STOP, FORWARD, BACKWARD, LEFT, RIGHT} contorlStates;
        uint16_t leftBitTrain;
        uint16_t rightBitTrain;
        bool leftDebounced = false;
        bool rightDebounced = false;
        bool prevLeftSwitch;
        bool prevRightSwitch;
        uint8_t PROGMEM leds[2] = {
            MINI_GONK_LED_1_PIN,            
            MINI_GONK_LED_2_PIN,
        };
        bool ledStates[2] = {
            false,
            false,
        };
        uint32_t ledTimers[2] = {
            0,
            0,
        };
        uint16_t ledIntervals[2] = {
            500,
            1000,
        };
        void initMotion();
        void motion();
        void debounce();
        void motorsOff();
        void handeButtons();
        void runMotors();
        void ledBlink();
};