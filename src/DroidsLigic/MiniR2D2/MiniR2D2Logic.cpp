#include "MiniR2D2Logic.h"

void MiniR2D2Logic::init()
{
    controller.init();
    player.init();
    pinMode(MINI_R2D2_RANDOM_SEED_PIN, INPUT);

    esc2.setup(
        MINI_R2D2_ESC_1_PIN,
        MINI_R2D2_CENTER_ESC_MICROSECONDS,
        MINI_R2D2_MIN_ESC_MICROSECONDS,
        MINI_R2D2_MAX_ESC_MICROSECONDS,
        MINI_R2D2_ESC_1_REVERSE
    );
    esc1.setup(
        MINI_R2D2_ESC_2_PIN,
        MINI_R2D2_CENTER_ESC_MICROSECONDS,
        MINI_R2D2_MIN_ESC_MICROSECONDS,
        MINI_R2D2_MAX_ESC_MICROSECONDS,
        MINI_R2D2_ESC_2_REVERSE
    );

    esc2.init();
    esc1.init();

    driveSystem.init(&esc1, &esc2);

    headServo.setup(
        MINI_R2D2_HEAD_SERVO_PIN
    );

    leftArmServo.setup(
        MINI_R2D2_LEFT_ARM_SERVO_PIN,
        MINI_R2D2_LEFT_ARM_SERVO_CENTER_ANGLE,
        MINI_R2D2_LEFT_ARM_SERVO_ANGLE_LIMIT
    );

    rightArmServo.setup(
        MINI_R2D2_RIGHT_ARM_SERVO_PIN,
        MINI_R2D2_RIGHT_ARM_SERVO_CENTER_ANGLE,
        MINI_R2D2_RIGHT_ARM_SERVO_ANGLE_LIMIT
    );

    shoulderServo.setup(
        MINI_R2D2_SHOULDER_SERVO_PIN,
        MINI_R2D2_SHOULDER_SERVO_CENTER_ANGLE
    );

    centerLiftServo.setup(
        MINI_R2D2_CENTER_LIFT_SERVO_PIN,
        MINI_R2D2_CENTER_LIFT_SERVO_CENTER_ANGLE
    );

    headServo.init();
    leftArmServo.init();
    rightArmServo.init();
    shoulderServo.init();
    centerLiftServo.init();

    animationRunnrer.setup(&leftArmServo, &rightArmServo, &shoulderServo, &centerLiftServo);

    pixel.begin();
    pixel.show();
    pixel.setBrightness(128);

    servoDriver.begin();
    servoDriver.setPWMFreq(50);

    lightLogic.init(&pixel, &servoDriver);
}

void MiniR2D2Logic::run()
{
    controller.update();

    driveSystem.run(controller.getLeftY(), controller.getRightX());

    //  if (controller.squareButtonClick() || animationRunnrer.isRunnung(0))
    // if (controller.squareButtonClick())
    // {
    //     if (state) {
    //         servoDriver.setPWM(3, 0, 240); // up
    //     } else {
    //         servoDriver.setPWM(3, 0, 460); //down
    //     }
    //     state = !state;
    // }

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
        randomSeed(analogRead(MINI_R2D2_RANDOM_SEED_PIN));
        player.playFile(random(1, 54));
    }

    headServo.run(controller.getBrakeThrottleMixed());

    lightLogic.runNeopixelLedLight();

    moveHoloprojector();
}

void MiniR2D2Logic::moveHoloprojector()
{
    for (uint8_t i = 0; i < 3; i++) {
        if (millis() - holoprojectorTimers[i] >= holoprojectorIntervals[i]) {
            holoprojectorTimers[i] = millis();
            randomSeed(analogRead(MINI_R2D2_RANDOM_SEED_PIN));
            

            holoprojectorStates[i] = !holoprojectorStates[i];
            
            if (holoprojectorStates[i]) {
                servoDriver.setPWM(i, 0, random(MINI_R2D2_HOLOPROJECTOR_MIN_PVM, MINI_R2D2_HOLOPROJECTOR_MAX_PVM));
                holoprojectorIntervals[i] = random(300, 500);
            } else {
                servoDriver.setPWM(i, 0, MINI_R2D2_HOLOPROJECTOR_CENTER_PVM);
                holoprojectorIntervals[i] = random(3000, 5000);
            }
        }
    }
}