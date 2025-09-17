#include "MiniR5D4Logic.h"

void MiniR5D4Logic::init()
{
    controller.init();
    player.init();
    pinMode(MINI_R5D4_RANDOM_SEED_PIN, INPUT);

    esc2.setup(
        MINI_R5D4_ESC_1_PIN,
        MINI_R5D4_CENTER_ESC_MICROSECONDS,
        MINI_R5D4_MIN_ESC_MICROSECONDS,
        MINI_R5D4_MAX_ESC_MICROSECONDS,
        MINI_R5D4_ESC_1_REVERSE
    );
    esc1.setup(
        MINI_R5D4_ESC_2_PIN,
        MINI_R5D4_CENTER_ESC_MICROSECONDS,
        MINI_R5D4_MIN_ESC_MICROSECONDS,
        MINI_R5D4_MAX_ESC_MICROSECONDS,
        MINI_R5D4_ESC_2_REVERSE
    );

    esc2.init();
    esc1.init();

    driveSystem.init(&esc1, &esc2);

    headServo.setup(
        MINI_R5D4_HEAD_SERVO_PIN
    );

    leftArmServo.setup(
        MINI_R5D4_LEFT_ARM_SERVO_PIN,
        MINI_R5D4_LEFT_ARM_SERVO_CENTER_ANGLE,
        MINI_R5D4_LEFT_ARM_SERVO_ANGLE_LIMIT
    );

    rightArmServo.setup(
        MINI_R5D4_RIGHT_ARM_SERVO_PIN,
        MINI_R5D4_RIGHT_ARM_SERVO_CENTER_ANGLE,
        MINI_R5D4_RIGHT_ARM_SERVO_ANGLE_LIMIT
    );

    shoulderServo.setup(
        MINI_R5D4_SHOULDER_SERVO_PIN,
        MINI_R5D4_SHOULDER_SERVO_CENTER_ANGLE
    );

    centerLiftServo.setup(
        MINI_R5D4_CENTER_LIFT_SERVO_PIN,
        MINI_R5D4_CENTER_LIFT_SERVO_CENTER_ANGLE
    );

    headServo.init();
    leftArmServo.init();
    rightArmServo.init();
    shoulderServo.init();
    centerLiftServo.init();

    animationRunnrer.setup(&leftArmServo, &rightArmServo, &shoulderServo, &centerLiftServo);
}

void MiniR5D4Logic::run()
{
    controller.update();

    driveSystem.run(controller.getLeftY(), controller.getRightX());

    if (controller.triangleButtonClick() || animationRunnrer.isRunnung(0))
    {
        animationRunnrer.run(0);
    }

    if (controller.croossButtonClick() || animationRunnrer.isRunnung(1))
    {
        animationRunnrer.run(1);
    }

    if (controller.circleButtonClick() || animationRunnrer.isRunnung(2))
    {
        animationRunnrer.run(2);
    }

    if (controller.r1ButtonClick())
    {
        animationRunnrer.stop();
    }

    if (controller.dPadUpClick()) {
        player.playFile(55);
    }

    if (controller.dPadDownClick()) {
        player.playFile(56);
    }

    if (controller.l1ButtonClick()) {
        randomSeed(analogRead(MINI_R5D4_RANDOM_SEED_PIN));
        player.playFile(random(1, 54));
    }

    headServo.run(controller.getBrakeThrottleMixed());
}