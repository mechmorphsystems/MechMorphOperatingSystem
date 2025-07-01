#include "BR2ULogic.h"

void BR2ULogic::init()
{
    controller.init();
    player.init();
    pinMode(BR2U_RANDOM_SEED_PIN, INPUT);

    esc2.setup(
        BR2U_ESC_1_PIN,
        BR2U_CENTER_ESC_MICROSECONDS,
        BR2U_MIN_ESC_MICROSECONDS,
        BR2U_MAX_ESC_MICROSECONDS,
        BR2U_ESC_1_REVERSE
    );
    esc1.setup(
        BR2U_ESC_2_PIN,
        BR2U_CENTER_ESC_MICROSECONDS,
        BR2U_MIN_ESC_MICROSECONDS,
        BR2U_MAX_ESC_MICROSECONDS,
        BR2U_ESC_2_REVERSE
    );

    esc2.init();
    esc1.init();

    headServo.setup(
        BR2U_HEAD_SERVO_PIN
    );

    leftHandServo.setup(
        BR2U_LEFT_HAND_SERVO_PIN,
        BR2U_LEFT_HAND_SERVO_CENTER_ANGLE,
        BR2U_LEFT_HAND_SERVO_ANGLE_LIMIT
    );

    rightHandServo.setup(
        BR2U_RIGHT_HAND_SERVO_PIN,
        BR2U_RIGHT_HAND_SERVO_CENTER_ANGLE,
        BR2U_RIGHT_HAND_SERVO_ANGLE_LIMIT
    );

    canDoorServo.setup(
        BR2U_CAN_DOOR_SERVO_PIN
    );

    leftCanServo.setup(
        BR2U_LEFT_CAN_SERVO_PIN
    );

    rightCanServo.setup(
        BR2U_RIGHT_CAN_SERVO_PIN
    );

    headServo.init();
    leftHandServo.init();
    rightHandServo.init();
    leftCanServo.init();
    rightCanServo.init();
    canDoorServo.init();

    animationRunnrer.setup(&canDoorServo, &leftCanServo, &rightCanServo);
}

void BR2ULogic::run()
{
    controller.update();

    runMotor();
    canMotion();

    if (controller.dPadUpClick()) {
        player.playFile(55);
    }

    if (controller.dPadDownClick()) {
        player.playFile(56);
    }

    if (controller.l1ButtonClick()) {
        randomSeed(analogRead(BR2U_RANDOM_SEED_PIN));
        player.playFile(random(1, 54));
    }

    headServo.run(controller.getBrakeThrottleMixed());
}

void BR2ULogic::runMotor()
{
    yValue = controller.getLeftY();
    xValue = controller.getRightX();

    rawLeft = xValue + yValue;
    rawRight = xValue - yValue;

    diff = abs(abs(xValue) - abs(yValue));
    rawLeft = rawLeft < 0 ? rawLeft - diff : rawLeft + diff;
    rawRight = rawRight < 0 ? rawRight - diff : rawRight + diff;

    rawLeft = constrain(rawLeft, -512, 512);
    rawRight = constrain(rawRight, -512, 512);
    esc2.run(rawLeft);
    esc1.run(rawRight);
    leftHandServo.run(rawLeft);
    rightHandServo.run(rawRight);
}

void BR2ULogic::canMotion()
{
    if (controller.squareButtonClick() || animationRunnrer.isRunnung(0))
    {
        animationRunnrer.run(0);
    }

    if (controller.circleButtonClick() || animationRunnrer.isRunnung(1))
    {
        animationRunnrer.run(1);
    }

    if (controller.triangleButtonClick() || animationRunnrer.isRunnung(2))
    {
        animationRunnrer.run(2);
    }

    if (controller.croossButtonClick() || animationRunnrer.isRunnung(3))
    {
        animationRunnrer.run(3);
    }

    if (controller.r1ButtonClick())
    {
        animationRunnrer.stop();
    }
}