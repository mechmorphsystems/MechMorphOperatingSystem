#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/DroidsLigic/DO/DoHeadMovement.h"
#include <Arduino.h>
#include "../../../DroidConfigs/DOConfig.h"
#include "../../Controllers/GamepadController.h"
#include "../../Movement/ImprovedServo.h"

class DoHeadMovement
{
    public:
        void init(GamepadController* controller);
        void run();
    private:
        GamepadController* controller;
        ImprovedServo mainBarServo;
        ImprovedServo headNodServo; //Pitch
        ImprovedServo headTurnServo; //Yaw
        ImprovedServo headTiltServo; //Bank
};

