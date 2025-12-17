#include "MiniR2D2Logic.h"

void MiniR2D2Logic::init()
{
    controller.init();
    player.init();
    pinMode(MINI_R2D2_RANDOM_SEED_PIN, INPUT);

    #ifdef ESC_DRIVE
    drive2.setup(
        MINI_R2D2_ESC_1_PIN,
        MINI_R2D2_CENTER_ESC_MICROSECONDS,
        MINI_R2D2_MIN_ESC_MICROSECONDS,
        MINI_R2D2_MAX_ESC_MICROSECONDS,
        MINI_R2D2_DRIVE_1_REVERSE
    );
    drive1.setup(
        MINI_R2D2_ESC_2_PIN,
        MINI_R2D2_CENTER_ESC_MICROSECONDS,
        MINI_R2D2_MIN_ESC_MICROSECONDS,
        MINI_R2D2_MAX_ESC_MICROSECONDS,
        MINI_R2D2_DRIVE_2_REVERSE
    );
    #endif

    #ifdef MX1508_DRIVE
    drive1.setup(
        MINI_R2D2_MX1508_1_PIN_1,
        MINI_R2D2_MX1508_1_PIN_2,
        MINI_R2D2_MX1508_MIN_PWM,
        MINI_R2D2_MX1508_MAX_PWM,
        MINI_R2D2_DRIVE_1_REVERSE
    );
    drive2.setup(
        MINI_R2D2_MX1508_2_PIN_1,
        MINI_R2D2_MX1508_2_PIN_2,
        MINI_R2D2_MX1508_MIN_PWM,
        MINI_R2D2_MX1508_MAX_PWM,
        MINI_R2D2_DRIVE_2_REVERSE
    );
    
    #endif

    drive1.init();
    drive2.init();

    driveSystem.init(&drive1, &drive2);

    #ifdef SERVO_HEAD
    headDrive.setup(
        MINI_R2D2_HEAD_SERVO_PIN
    );
    #endif

    #ifdef MX1508_HEAD
    headDrive.setup(
        MINI_R2D2_MX1508_HEAD_PIN_1,
        MINI_R2D2_MX1508_HEAD_PIN_2,
        MINI_R2D2_MX1508_MIN_PWM,
        MINI_R2D2_MX1508_MAX_PWM
    );
    #endif

    headDrive.init();

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

    leftArmServo.init();
    rightArmServo.init();
    shoulderServo.init();
    centerLiftServo.init();

    neoPixelLed.begin();
    neoPixelLed.show();
    neoPixelLed.setBrightness(128);

    servoDriver.begin();
    servoDriver.setPWMFreq(50);

    lightLogic.init(&neoPixelLed, &servoDriver);
    animationRunnrer.setup(
        &player,
        &driveSystem,
        &leftArmServo,
        &rightArmServo,
        &shoulderServo,
        &centerLiftServo,
        &neoPixelLed,
        &servoDriver
    );

    servoDriver.setPWM(3, 0, MINI_R2D2_PERISCOPE_DOWN_PVM);
    servoDriver.setPWM(4, 0, 4096); // low
}

void MiniR2D2Logic::run()
{
    controller.update();

    driveSystem.run(controller.getLeftY(), controller.getRightX());

    if (controller.triangleButtonClick() || animationRunnrer.isRunnung(0)) {
        animationRunnrer.run(0);
    }

    if (controller.croossButtonClick() || animationRunnrer.isRunnung(1)) {
        animationRunnrer.run(1);
    }

    if (controller.circleButtonClick() || animationRunnrer.isRunnung(2)) {
        animationRunnrer.run(2);
    }

    if (controller.squareButtonClick() || animationRunnrer.isRunnung(3)) {
        animationRunnrer.run(3);
    }


    if (controller.r1ButtonClick()) {
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

    headDrive.run(controller.getBrakeThrottleMixed());

    #ifdef NEO_PIXEL_LED
    lightLogic.runNeopixelLedLight();
    #endif

    #ifdef REGULAR_LED
    lightLogic.runRegularLedLight();
    #endif

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