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
}

void MiniCH33PLogic::run()
{
    controller.update();

    driveSystem.run(controller.getLeftY(), controller.getRightX());

    if (controller.dPadUpClick()) {
        player.playFile(55);
    }

    if (controller.dPadDownClick()) {
        player.playFile(56);
    }

    if (controller.l1ButtonClick()) {
        randomSeed(analogRead(MINI_CH_33P_RANDOM_SEED_PIN));
        player.playFile(random(1, 54));
    }

    headServo.run(controller.getBrakeThrottleMixed());
}