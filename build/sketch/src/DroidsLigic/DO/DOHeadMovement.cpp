#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/DroidsLigic/DO/DOHeadMovement.cpp"
#include "DoHeadMovement.h"

void DoHeadMovement::init(GamepadController* controller)
{
    DoHeadMovement::controller = controller;

    mainBarServo.setup(
        DO_MAIN_BAR_SERVO,
        DO_MAIN_BAR_SERVO_CENTRE_ANGLE,
        DO_MAIN_BAR_SERVO_ANGLE_LIMIT
    );
    headNodServo.setup(
        DO_HEAD_NOD_SERVO,
        DO_HEAD_NOD_SERVO_CENTRE_ANGLE,
        DO_HEAD_NOD_SERVO_ANGLE_LIMIT
    );
    headTurnServo.setup(
        DO_HEAD_TURN_SERVO,
        DO_HEAD_TURN_SERVO_CENTRE_ANGLE
    );
    headTiltServo.setup(
        DO_HEAD_TILT_SERVO,
        DO_HEAD_TILT_SERVO_CENTRE_ANGLE,
        DO_HEAD_TILT_SERVO_ANGLE_LIMIT, 
        true
    );

    mainBarServo.init();
    headNodServo.init();
    headTurnServo.init();
    headTiltServo.init();
}

void DoHeadMovement::run()
{
    mainBarServo.run(controller->getLeftY());
    headNodServo.run(-controller->getLeftY());
    headTurnServo.run(controller->getLeftX());
    headTiltServo.run(controller->getBrakeThrottleMixed());
}