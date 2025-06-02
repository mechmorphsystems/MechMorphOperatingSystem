#include "BR2ULogic.h"

void BR2ULogic::init()
{
    controller.init();
    player.init();
    pinMode(BR2U_RANDOM_SEED_PIN, INPUT);

    throttleEsc.setup(
        BR2U_THROTTLE_ESC_PIN,
        BR2U_CENTER_ESC_MICROSECONDS,
        BR2U_MIN_ESC_MICROSECONDS,
        BR2U_MAX_ESC_MICROSECONDS,
        BR2U_THROTTLE_ESC_REVERSE
    );
    steeringEsc.setup(
        BR2U_STEERING_ESC_PIN,
        BR2U_CENTER_ESC_MICROSECONDS,
        BR2U_MIN_ESC_MICROSECONDS,
        BR2U_MAX_ESC_MICROSECONDS,
        BR2U_STEERING_ESC_REVERSE
    );

    throttleEsc.init();
    steeringEsc.init();

    headServo.setup(
        BR2U_HEAD_SERVO_PIN
    );

    // leftHandServo.setup(
    //     BR2U_LEFT_HAND_SERVO_PIN
    // );

    // rightHandServo.setup(
    //     BR2U_RIGHT_HAND_SERVO_PIN
    // );

    canDoorServo.setup(
        BR2U_CAN_DOOR_SERVO_PIN
    );

    // leftCanServo.setup(
    //     BR2U_LEFT_CAN_SERVO_PIN
    // );

    // rightCanServo.setup(
    //     BR2U_RIGHT_CAN_SERVO_PIN
    // );

    headServo.init();
    // leftHandServo.init();
    // rightHandServo.init();
    canDoorServo.init();
    // leftCanServo.init();
    // rightCanServo.init();
    
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

    if (controller.r1ButtonClick()) {
        randomSeed(analogRead(BR2U_RANDOM_SEED_PIN));
        player.playFile(random(1, 54));
    }

    headServo.run(controller.getBrakeThrottleMixed());
}

void BR2ULogic::runMotor()
{
    throttleEsc.run(controller.getRightY());
    steeringEsc.run(controller.getRightX());
}

void BR2ULogic::canMotion()
{
    if (controller.triangleButtonClick()) {
        isOpenCanDoor = true;
        canDoorServo.writeAngle(0);
    }

    // if (isOpenCanDoor && controller.squareButtonClick()) {
    //     if (isLeftCanUp) {
    //         leftCanServo.writeAngle(90);
    //     } else {
    //         leftCanServo.writeAngle(110);
    //     }
        
    //     isLeftCanUp = !isLeftCanUp;
    // }

    // if (isOpenCanDoor && controller.circleButtonClick()) {
    //     if (isRightCanUp) {
    //         rightCanServo.writeAngle(90);
    //     } else {
    //         rightCanServo.writeAngle(180);
    //     }
        
    //     isRightCanUp = !isRightCanUp;
    // }
    

    if (controller.croossButtonClick()) {
        isOpenCanDoor = false;
        // leftCanServo.writeAngle(90);
        // rightCanServo.writeAngle(90);
        canDoorServo.writeAngle(90);
    }
}