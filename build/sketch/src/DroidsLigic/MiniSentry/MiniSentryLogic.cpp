#line 1 "/home/vasya/arduino/MechMorphOperatingSystem/src/DroidsLigic/MiniSentry/MiniSentryLogic.cpp"
#include "MiniSentryLogic.h"

void MiniSentryLogic::init()
{
    controller.init();

    esc1.setup(
        MINI_SENTRY_ESC_1_PIN,
        MINI_SENTRY_CENTER_ESC_MICROSECONDS,
        MINI_SENTRY_MIN_ESC_MICROSECONDS,
        MINI_SENTRY_MAX_ESC_MICROSECONDS
    );

    esc2.setup(
        MINI_SENTRY_ESC_2_PIN,
        MINI_SENTRY_CENTER_ESC_MICROSECONDS,
        MINI_SENTRY_MIN_ESC_MICROSECONDS,
        MINI_SENTRY_MAX_ESC_MICROSECONDS
    );

    esc3.setup(
        MINI_SENTRY_ESC_3_PIN,
        MINI_SENTRY_CENTER_ESC_MICROSECONDS,
        MINI_SENTRY_MIN_ESC_MICROSECONDS,
        MINI_SENTRY_MAX_ESC_MICROSECONDS
    );

    // leftDoorServo.setup(
    //     MINI_SENTRY_LEFT_DOOR_SERVO_PIN
    // );

    // rightDoorServo.setup(
    //     MINI_SENTRY_RIGHT_DOOR_SERVO_PIN
    // );

    // leftDoorServo.init();
    // rightDoorServo.init();
    // leftDoorServo.writeAngle(MINI_SENTRY_LEFT_DOOR_ZERO_ANGLE);
    // rightDoorServo.writeAngle(MINI_SENTRY_RIGHT_DOOR_ZERO_ANGLE);
    esc1;
    esc2;
    esc3;

}

void MiniSentryLogic::run()
{
    controller.update();

    esc1.run(controller.getBrakeThrottleMixed());
    esc2.run(controller.getBrakeThrottleMixed());
    esc3.run(controller.getBrakeThrottleMixed());

    // if (controller.squareButtonClick()) {
    //     leftDoorServo.writeAngle(180);
    //     rightDoorServo.writeAngle(0);
    // }

    // if (controller.croossButtonClick()) {
    //     leftDoorServo.writeAngle(MINI_SENTRY_LEFT_DOOR_ZERO_ANGLE);
    //     rightDoorServo.writeAngle(MINI_SENTRY_RIGHT_DOOR_ZERO_ANGLE);
    // }
    
}