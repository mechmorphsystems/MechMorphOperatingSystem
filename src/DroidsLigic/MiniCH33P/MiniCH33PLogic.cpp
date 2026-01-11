#include "MiniCH33PLogic.h"

void MiniCH33PLogic::init()
{
    controller.init();
    player.init();
    pinMode(MINI_CH_33P_RANDOM_SEED_PIN, INPUT);

    esc2.setup(
        MINI_CH_33P_ESC_1_PIN,
        MINI_CH_33P_CENTER_ESC_MICROSECONDS,
        MINI_CH_33P_MIN_ESC_MICROSECONDS,
        MINI_CH_33P_MAX_ESC_MICROSECONDS,
        MINI_CH_33P_ESC_1_REVERSE
    );
    esc1.setup(
        MINI_CH_33P_ESC_2_PIN,
        MINI_CH_33P_CENTER_ESC_MICROSECONDS,
        MINI_CH_33P_MIN_ESC_MICROSECONDS,
        MINI_CH_33P_MAX_ESC_MICROSECONDS,
        MINI_CH_33P_ESC_2_REVERSE
    );

    esc2.init();
    esc1.init();

    driveSystem.init(&esc1, &esc2);

    headServo.setup(
        MINI_CH_33P_HEAD_SERVO_PIN
    );

    armServo.setup(
        MINI_CH_33P_ARM_SERVO_PIN,
        MINI_CH_33P_ARM_SERVO_CENTER_ANGLE
    );

    headServo.init();
    armServo.init();

    servoDriver.begin();
    servoDriver.setPWMFreq(50);

    animationRunner.setup(&armServo);

    for (uint8_t i = 0; i < 9; i++) {
        servoDriver.setPWM(i, 0, 4096); // low
    }
}

void MiniCH33PLogic::run()
{
    controller.update();

    driveSystem.run(controller.getLeftY(), controller.getRightX());

    if (controller.l1ButtonClick()) {
        randomSeed(analogRead(MINI_CH_33P_RANDOM_SEED_PIN));
        player.playFile(random(1, 31));
    }

    if (controller.triangleButtonClick() || animationRunner.isRunnung(0)) {
        animationRunner.run(0);
    }

    if (controller.croossButtonClick()) {
        animationRunner.stop();
    }

    headServo.run(controller.getBrakeThrottleMixed());

    frontLogicLight();
    rearLogicLight();
}

void MiniCH33PLogic::frontLogicLight()
{
    if (millis() - frontLogicTimer > 100)
    {
        frontLogicTimer = millis();

        if (frontLogicPointer <= 0) {
            frontLogicRandomPointer = random(1, 5);
        }

        if (0 == frontLogicState) {
            if (frontLogicPointer > frontLogicRandomPointer) {
                frontLogicState = 1;
            } else {
                servoDriver.setPWM(frontLogicPointer, 4096, 0); // high
            }

            frontLogicPointer++;
        } else {
            if (frontLogicPointer <= 0) {
                frontLogicState = 0;
            }

            servoDriver.setPWM(frontLogicPointer, 0, 4096); // low

            frontLogicPointer--;
        }
    }
}

void MiniCH33PLogic::rearLogicLight()
{
    for (uint8_t i = 0; i < 4; i++) {
        if (millis() - rearLogicTimers[i] >= rearLogicIntervals[i]) {
            rearLogicTimers[i] = millis();
            randomSeed(analogRead(MINI_CH_33P_RANDOM_SEED_PIN));
            rearLogicIntervals[i] = random(1000);

            rearLogicStates[i] = !rearLogicStates[i];
            if (rearLogicStates[i] ) {
                servoDriver.setPWM(i + 6, 4096, 0); // high
            } else {
                servoDriver.setPWM(i + 6, 0, 4096); // low
            }
        }
    }
}