#include "FerryRacerLogic.h"

void FerryRacerLogic::init()
{
    controller.init();

    throttleEsc.setup(
        FERRY_RACER_THROTTLE_ESC_PIN,
        FERRY_RACER_CENTER_ESC_MICROSECONDS,
        FERRY_RACER_MIN_ESC_MICROSECONDS,
        FERRY_RACER_MAX_ESC_MICROSECONDS,
        FERRY_RACER_ESC_REVERSE
    );

    throttleEsc.init();

    steeringServo.setup(
        FERRY_RACER_STEERING_SERVO_PIN,
        FERRY_RACER_SERVO_ZERO_ANGLE,
        FERRY_RACER_SERVO_ANGLE_LIMIT,
        FERRY_RACER_SERVO_REVERSE
    );

    headServo.setup(
        FERRY_RACER_HEAD_SERVO_PIN
    );

    steeringServo.init();
    headServo.init();

    driveSystem.init(&throttleEsc, &steeringServo);

    pinMode(FERRY_RACER_LEFT_LED_PIN, OUTPUT);
    pinMode(FERRY_RACER_RIGHT_LED_PIN, OUTPUT);
}

void FerryRacerLogic::run()
{
    controller.update();

    driveSystem.run(controller.getLeftY(), controller.getRightX());
    headServo.run(controller.getBrakeThrottleMixed());

    if (controller.triangleButtonClick()) {
        digitalWrite(FERRY_RACER_LEFT_LED_PIN, HIGH);
        digitalWrite(FERRY_RACER_RIGHT_LED_PIN, HIGH);
    }
    
    if (controller.croossButtonClick()) {
        digitalWrite(FERRY_RACER_LEFT_LED_PIN, LOW);
        digitalWrite(FERRY_RACER_RIGHT_LED_PIN, LOW);
    }
}